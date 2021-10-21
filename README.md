# GenieACS-QT-smallGUI
Small GUI enables fast configuration changes on supported devices.
# Use Case
Instead of searching correct configuration in GenieACS we can access only selected preprogrammed options for devices.
GUI supports:
- Tenda AC8
- TP-Link DECO M4R(only some units support TR-069)
Other devices will be displayed without ability to edit any settings.
Knowing device serial number we can quickly find it and edit:
- SSID
- SSID password
- PPPoE login
- PPPoE password
This is more appropriate for people that shouldn't have full access.
# Adding settings and models
Supported models and options can be added with factory pattern. **Cpe** class in **cpe.h** defines base class for all models. New models can be addded by copying **CpeAC8** and editing nodes. Finally all models identified by product class needs to be added to **Cpewindow::setPointer** in form of "if" statement.
## Summary
This solution is meant to be quickly modified for limited options used by provider.
Not to be-all and end-all for all TR-069 models and configurations.
