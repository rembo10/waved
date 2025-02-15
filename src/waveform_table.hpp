/**
 * @file
 * SPDX-FileCopyrightText: 2021 Mattéo Delabre <spam@delab.re>
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef WAVED_WAVEFORM_TABLE_HPP
#define WAVED_WAVEFORM_TABLE_HPP

#include "defs.hpp"
#include <utility>
#include <cstdint>
#include <iostream>
#include <array>
#include <vector>
#include <optional>

/**
 * Waveform mode.
 *
 * Users can usually choose from several kinds of waveforms that provide
 * different trade-offs between image fidelity and rendering speed.
 */
using Mode = std::uint8_t;

/**
 * Temperature (in Celsius).
 *
 * Knowing the EPD’s current temperature is needed for selecting the right
 * waveform to use to transition a given cell.
 */
using Temperature = std::int8_t;

/** Load an electrophoretic display (EPD) waveform definition table. */
class WaveformTable
{
public:
    /** Create an empty waveform table. */
    WaveformTable();

    /** Discover the path to the appropriate WBF file for the current panel. */
    static std::optional<std::string> discover_wbf_file();

    /**
     * Read waveform table definitions from a WBF file.
     *
     * @param path Path to the file.
     * @return Parsed waveform table.
     * @throws std::runtime_error If a parsing error occurs.
     */
    static WaveformTable from_wbf(const char* path);

    /**
     * @overload
     * @param file Opened stream to read from.
     * @throws std::runtime_error If a parsing error occurs.
     * @throws std::system_error If the file cannot be read.
     */
    static WaveformTable from_wbf(std::istream& file);

    /**
     * Lookup the waveform for the given mode and temperature.
     *
     * @param mode Mode.
     * @param temperature Temperature in Celsius.
     * @return Corresponding waveform.
     * @throws std::out_of_range If the given mode or temperature is not
     * supported.
     */
    const Waveform& lookup(int mode, int temperature) const;
    using Lookup = std::vector<std::vector<std::size_t>>;

    /** Get the display frame rate. */
    std::uint8_t get_frame_rate() const;

    /** Get the available operating temperature thresholds. */
    const std::vector<Temperature>& get_temperatures() const;

    /** Get the number of available modes. */
    Mode get_mode_count() const;

private:
    // Display frame rate
    std::uint8_t frame_rate;

    // Number of available modes
    Mode mode_count;

    // Set of temperature thresholds
    // The last value is the maximal operating temperature
    std::vector<Temperature> temperatures;

    // All available waveforms. This table may be smaller than
    // `(temperatures.size() - 1) * mode_count` since some modes/temperatures
    // combinations reuse the same waveform
    std::vector<Waveform> waveforms;

    // Vector for looking the waveform corresponding to a mode and temperature
    Lookup waveform_lookup;
};

#endif // WAVED_WAVEFORM_TABLE_HPP
