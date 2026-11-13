#!/usr/bin/env python3
"""
PLC simulator — exposes an S7-1500-like OPC UA address space.

Run: python3 plc_sim.py  (after: pip install asyncua)
Endpoint: opc.tcp://0.0.0.0:4840
Namespace index: 3  (string node ids: ns=3;s="<DB>".Tag)
"""
import asyncio
import random
import sys
from asyncua import Server, ua

async def main():
    server = Server()
    await server.init()
    server.set_endpoint("opc.tcp://0.0.0.0:4840")
    server.set_server_name("S7-1500 PLC Simulator")

    # Register namespace like a real S7-1500 project
    uri = "http://siemens.com/s7-1500/opcua"
    ns = await server.register_namespace(uri)  # typically ns=2 or 3
    print(f"Namespace index: {ns}")

    # Create objects folder
    objects = server.nodes.objects

    # ConveyorDB (Data Block)
    conveyor_db = await objects.add_object(ns, "ConveyorDB")
    speed = await conveyor_db.add_variable(ns, "Speed", 0.0)
    await speed.set_writable()
    await speed.set_attribute(ua.AttributeIds.Description, ua.LocalizedText("Conveyor speed m/s"))
    setpoint = await conveyor_db.add_variable(ns, "Setpoint", 1.5)
    await setpoint.set_writable()
    await setpoint.set_attribute(ua.AttributeIds.Description, ua.LocalizedText("Speed setpoint m/s"))
    load = await conveyor_db.add_variable(ns, "Load", 0.0)
    await load.set_writable()
    await load.set_attribute(ua.AttributeIds.Description, ua.LocalizedText("Conveyor load factor 0..1"))

    # MotorDB
    motor_db = await objects.add_object(ns, "MotorDB")
    temp = await motor_db.add_variable(ns, "Temperature", 45.0)
    await temp.set_writable()
    await temp.set_attribute(ua.AttributeIds.Description, ua.LocalizedText("Motor temperature C"))
    current = await motor_db.add_variable(ns, "Current", 0.0)
    await current.set_writable()
    await current.set_attribute(ua.AttributeIds.Description, ua.LocalizedText("Motor current A"))

    # Status word (bool-ish)
    status = await objects.add_variable(ns, "StatusWord", 0, ua.VariantType.UInt16)
    await status.set_writable()

    # Subscription-friendly: set sampling interval hints
    for var in [speed, setpoint, load, temp, current, status]:
        await var.set_sampling_interval(100)  # ms

    print("Starting server...")
    async with server:
        # Simulate process: conveyor physics + noise
        speed_val = 0.0
        while True:
            await asyncio.sleep(0.1)
            # Simple first-order lag toward setpoint
            sp = await setpoint.get_value()
            speed_val += (sp - speed_val) * 0.1
            # Add load effect + noise
            ld = await load.get_value()
            speed_val *= (1.0 - 0.1 * ld)
            speed_val += random.uniform(-0.01, 0.01)
            speed_val = max(0.0, min(5.0, speed_val))
            await speed.write_value(speed_val)

            # Temperature follows current with lag
            cur = 0.5 + 2.0 * abs(speed_val - sp) + random.uniform(-0.05, 0.05)
            await current.write_value(cur)
            t = await temp.get_value()
            t += (cur * 2.0 - t) * 0.02
            await temp.write_value(t)

            # Status word: bit0=running, bit1=at_setpoint
            sw = 1 if speed_val > 0.1 else 0
            sw |= 2 if abs(speed_val - sp) < 0.05 else 0
            await status.write_value(sw)

if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nStopped")
        sys.exit(0)
