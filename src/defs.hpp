/**
 * @file Shared definitions for waved.
 * SPDX-FileCopyrightText: 2021 Mattéo Delabre <spam@delab.re>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef WAVED_DEFS_HPP
#define WAVED_DEFS_HPP

#include <array>
#include <cstdint>
#include <vector>

/**
 * Phase types.
 *
 * A phase is a command sent to an individual EPD cell in one frame.
 */
enum class Phase : std::uint8_t
{
    // Leave the cell in its present state
    Noop = 0b00,

    // Apply a current to bring black particles to the top
    Black = 0b01,

    // Apply a current to bring white particles to the top
    White = 0b10,
};

/**
 * Cell grayscale intensity (5 bits).
 *
 * Only even values are used. 0 denotes full black, 30 full white.
 */
using Intensity = std::uint8_t;
constexpr std::uint8_t intensity_values = 1 << 5;

/**
 * Phase matrix.
 *
 * Lookup table that gives the appropriate phase to apply to transition
 * between two intensities.
 */
using PhaseMatrix
    = std::array<std::array<Phase, intensity_values>, intensity_values>;

/**
 * Waveform.
 *
 * A waveform is a sequence of phase matrices used to transition an EPD cell
 * from a given grayscale intensity to another.
 */
using Waveform = std::vector<PhaseMatrix>;

/** Screen region. */
struct Region
{
    std::uint32_t top;
    std::uint32_t left;
    std::uint32_t width;
    std::uint32_t height;
};

#endif // WAVED_DEFS_HPP
