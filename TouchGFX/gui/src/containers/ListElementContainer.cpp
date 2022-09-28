#include <gui/containers/ListElementContainer.hpp>

ListElementContainer::ListElementContainer()
{

}

void ListElementContainer::initialize()
{
    ListElementContainerBase::initialize();
}

void ListElementContainer::set_name(Unicode::UnicodeChar *name)
{
  Unicode::snprintf(DeviceNameBuffer, DEVICENAME_SIZE, "%s", name);
  DeviceName.invalidate();
}

void ListElementContainer::set_unit(Unicode::UnicodeChar *unit)
{
  Unicode::snprintf(DeviceUnitBuffer, DEVICEUNIT_SIZE, "%s", unit);
  DeviceUnit.invalidate();
}

void ListElementContainer::set_value(int32_t value)
{
  Unicode::snprintf(DeviceValueBuffer, DEVICEVALUE_SIZE, "%d", value);
  DeviceValue.invalidate();
}
