/**
* @file KatanaDrawable.cpp
 * @author Kyle Nguyen
 */

#include "pch.h"
#include "KatanaDrawable.h"

/**
 * Constructor
 * @param name The drawable name
 * @param filename The filename for the katana image
 */
KatanaDrawable::KatanaDrawable(const std::wstring& name, const std::wstring& filename)
    : ImageDrawable(name, filename)
{
}

/**
 * Hit test for the katana
 * @param pos Position to test
 * @return true if the katana was clicked
 */
bool KatanaDrawable::HitTest(wxPoint pos)
{
    return ImageDrawable::HitTest(pos);
}