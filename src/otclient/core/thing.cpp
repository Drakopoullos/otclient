/*
 * Copyright (c) 2010-2011 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "thing.h"
#include "spritemanager.h"
#include <framework/graphics/graphics.h>

Thing::Thing(Otc::ThingType type) : m_id(0), m_type(type)
{
    m_xPattern = 0;
    m_yPattern = 0;
    m_zPattern = 0;
    m_animation = 0;
}

void Thing::setPosition(const Position& position)
{
    Position oldPosition = m_position;
    m_position = position;

    onPositionChange(oldPosition);
}

void Thing::internalDraw(int x, int y, int layers, Otc::SpriteMask mask)
{
    const ThingAttributes& attributes = getAttributes();

    for(int yi = 0; yi < attributes.height; yi++) {
        for(int xi = 0; xi < attributes.width; xi++) {
            int sprIndex = xi +
                    yi * attributes.width +
                    layers * attributes.width * attributes.height +
                    m_xPattern * attributes.width * attributes.height * attributes.layers +
                    m_yPattern * attributes.width * attributes.height * attributes.layers * attributes.xPattern +
                    m_zPattern * attributes.width * attributes.height * attributes.layers * attributes.xPattern * attributes.yPattern +
                    m_animation * attributes.width * attributes.height * attributes.layers * attributes.xPattern * attributes.yPattern * attributes.zPattern;

            int spriteId = attributes.sprites[sprIndex];
            if(!spriteId)
                continue;

            TexturePtr spriteTex = g_sprites.getSpriteTexture(spriteId, mask);

            Rect drawRect((x - xi*32) - attributes.xDisplacment,
                          (y - yi*32) - attributes.yDisplacment,
                          32, 32);
            g_graphics.drawTexturedRect(drawRect, spriteTex);
        }
    }
}
