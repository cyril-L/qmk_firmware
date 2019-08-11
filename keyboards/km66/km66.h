/* Copyright 2019 Cyril Lugan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e10, e11, e12, e13, \
    d00, d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, \
    c00, c01, c02, c03, c04, c05,      c07, c08, c09, c10, c11, c12, c13, \
    b00, b01, b02, b03, b04, b05, b06, b07, b08, b09, b10, b11, b12, b13, \
    a00,      a02, a03, a04, a05, a06, a07, a08, a09, a10,           a13  \
) \
{ \
	{ e00, e01, e02, e03, e04, e05, e06, e07, e08, e09, e10, e11, e12, e13}, \
    { d00, d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13}, \
    { c00, c01, c02, c03, c04, c05, KC_NO, c07, c08, c09, c10, c11, c12, c13}, \
    { b00, b01, b02, b03, b04, b05, b06, b07, b08, b09, b10, b11, b12, b13}, \
    { a00, KC_NO, a02, a03, a04, a05, a06, a07, a08, a09, a10, KC_NO, KC_NO, a13} \
}
