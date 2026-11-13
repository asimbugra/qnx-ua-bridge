#!/usr/bin/env python3
"""
Browse an OPC UA server and emit tags.example.json for the bridge.
Usage: python3 tagmap_gen.py opc.tcp://host:4840 [output.json]
"""
import asyncio
import json
import sys
from asyncua import Client, ua

async def browse(node, path_parts, out):
    children = await node.get_children()
    for child in children:
        browsename = await child.read_browse_name()
        name = browsename.Name
        new_path = "/".join(path_parts + [name]) if path_parts else name
        try:
            node_class = await child.read_node_class()
            if node_class == ua.NodeClass.Variable:
                dtype = (await child.read_data_type()).Identifier
                # Map common types
                type_map = {
                    ua.VariantType.Float: "float",
                    ua.VariantType.Double: "double",
                    ua.VariantType.Int32: "int32",
                    ua.VariantType.UInt32: "uint32",
                    ua.VariantType.Int16: "int16",
                    ua.VariantType.UInt16: "uint16",
                    ua.VariantType.Boolean: "bool",
                    ua.VariantType.String: "string",
                }
                vtype = type_map.get(dtype, "double")
                access = "read"
                # Check writable
                attr = await child.read_attribute(ua.AttributeIds.AccessLevel)
                if attr.Value.Value & 0x02:  # writable
                    access = "write" if not (attr.Value.Value & 0x01) else "readwrite"
                out.append({
                    "path": new_path,
                    "node_id": child.nodeid.to_string(),
                    "type": vtype,
                    "access": access,
                    "sampling_interval_ms": 100,
                })
        except Exception:
            pass
        # Recurse into objects
        if (await child.read_node_class()) == ua.NodeClass.Object:
            await browse(child, path_parts + [name], out)

async def main(url, out_path):
    async with Client(url=url) as client:
        root = client.nodes.objects
        out = []
        await browse(root, [], out)
        # Filter: keep only vars under DataBlock-like objects (name endswith DB)
        filtered = [t for t in out if any(p.endswith("DB") for p in t["path"].split("/")[:-1])]
        if not filtered:
            filtered = out  # fallback
        cfg = {"server": {"url": url, "security": "none", "reconnect_min_ms": 500, "reconnect_max_ms": 30000}, "tags": filtered}
        with open(out_path, "w") as f:
            json.dump(cfg, f, indent=2)
        print(f"Wrote {len(filtered)} tags to {out_path}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: tagmap_gen.py <opc.tcp://host:port> [output.json]")
        sys.exit(1)
    url = sys.argv[1]
    out = sys.argv[2] if len(sys.argv) > 2 else "tags.example.json"
    asyncio.run(main(url, out))
