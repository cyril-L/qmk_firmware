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

// place overrides here

// To check for macOS, dont’t know what is the deal with TAP_HOLD_CAPS_DELAY

// Needs to be high enough so I can double tap shift to get a caps lock
// Needs to be low enough so I can use mod tap…
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
