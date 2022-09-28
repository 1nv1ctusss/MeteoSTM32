#ifndef LISTELEMENTCONTAINER_HPP
#define LISTELEMENTCONTAINER_HPP

#include <gui_generated/containers/ListElementContainerBase.hpp>

class ListElementContainer : public ListElementContainerBase
{
public:
    ListElementContainer();
    virtual ~ListElementContainer() {}

    virtual void initialize();
    virtual void set_name(Unicode::UnicodeChar *name);
    virtual void set_unit(Unicode::UnicodeChar *unit);
    virtual void set_value(int32_t value);
protected:
};

#endif // LISTELEMENTCONTAINER_HPP
