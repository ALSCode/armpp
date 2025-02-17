#pragma once

#include <cstdint>

extern "C" void
system_init();
extern "C" void
system_tick();

namespace armpp::hal::system {

// TODO frequency and chrono types

class clock {
public:
    using tick_type = std::uint32_t;

public:
    clock(clock const&) = delete;
    clock(clock&&)      = delete;

    void
    increment_tick()
    {
        ++tick_;
    }

    tick_type
    tick() const
    {
        return tick_;
    }

    tick_type
    system_frequency() const
    {
        return system_frequency_;
    }

    tick_type
    ticks_per_millisecond() const
    {
        return system_frequency_ / 1000;
    }

public:
    static clock const&
    instance();

private:
    friend void ::system_init();
    friend void ::system_tick();

    clock() = default;

    static clock&
    mutable_instance();

    void
    system_frequency(tick_type freq)
    {
        system_frequency_ = freq;
    }

    tick_type system_frequency_;
    tick_type tick_;
};

}    // namespace armpp::hal::system
