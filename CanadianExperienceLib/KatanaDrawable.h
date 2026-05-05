/**
* @file KatanaDrawable.h
 * @author Kyle Nguyen
 *
 * A drawable that displays a katana prop
 */

#ifndef CANADIANEXPERIENCE_KATANADRAWABLE_H
#define CANADIANEXPERIENCE_KATANADRAWABLE_H

#include "ImageDrawable.h"

/**
 * A drawable that displays a katana prop.
 * The katana can be held by any actor as a prop.
 */
class KatanaDrawable : public ImageDrawable {
public:
    KatanaDrawable(const std::wstring& name, const std::wstring& filename);

    /**
     * Katana is not movable — it stays attached to the actor
     * @return false always
     */
    bool IsMovable() override { return false; }

    bool HitTest(wxPoint pos) override;
};

#endif //CANADIANEXPERIENCE_KATANADRAWABLE_H