# Lessons learned

One dated entry per problem actually hit:

## YYYY-MM-DD - short problem title
- Symptom:
- Root cause:
- Fix:

## 2026-11-13 - asyncua write_attribute with LocalizedText requires DataValue wrapper
- Symptom: `AttributeError: 'LocalizedText' object has no attribute 'StatusCode'` when setting Description attribute on server variables.
- Root cause: asyncua's `write_attribute` expects a `DataValue` containing a `Variant`, not a raw `LocalizedText`. The server's attribute service validates the StatusCode field which only exists on DataValue.
- Fix: Wrap all attribute writes: `await var.write_attribute(ua.AttributeIds.Description, ua.DataValue(ua.Variant(ua.LocalizedText("..."), ua.VariantType.LocalizedText)))`

## 2026-11-13 - asyncua add_variable with explicit type needs Variant constructor for non-double
- Symptom: `BadTypeMismatch: The value supplied for the attribute is not of the same type as the attribute's value` when writing UInt16 StatusWord.
- Root cause: `add_variable(ns, "StatusWord", 0, ua.VariantType.UInt16)` creates the variable but the initial value is a Python int (Int64). Subsequent `write_value(sw)` also passes Python int. The server rejects type mismatch.
- Fix: Use `ua.Variant(value, ua.VariantType.UInt16)` for both initial value and all writes: `ua.Variant(0, ua.VariantType.UInt16)` and `ua.Variant(sw, ua.VariantType.UInt16)`.
