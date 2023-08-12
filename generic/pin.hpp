////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018 Dimitry Ishenko
// Contact: dimitry (dot) ishenko (at) (gee) mail (dot) com
//
// Distributed under the GNU GPL license. See the LICENSE.md file for details.

////////////////////////////////////////////////////////////////////////////////
#ifndef GPIO_GENERIC_PIN_HPP
#define GPIO_GENERIC_PIN_HPP

////////////////////////////////////////////////////////////////////////////////
#include "pin_base.hpp"

#include <asio/io_context.hpp>
#include <asio/posix/stream_descriptor.hpp>
#include <atomic>
#include <cstdint>
#include <future>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
namespace gpio
{
namespace generic
{

////////////////////////////////////////////////////////////////////////////////
class chip;

////////////////////////////////////////////////////////////////////////////////
class pin : public pin_base
{
public:
    ////////////////////
    pin(asio::io_context&, generic::chip*, gpio::pos);
    virtual ~pin() override;

    ////////////////////
    virtual void mode(gpio::mode, gpio::flag, gpio::state) override;

    virtual void detach() override;
    virtual bool is_detached() const noexcept override { return !fd_.is_open(); }

    ////////////////////
    virtual void set(gpio::state = on) override;
    virtual gpio::state state() override;

    virtual void period(nsec) override;
    virtual void pulse(nsec) override;

private:
    ////////////////////
    asio::posix::stream_descriptor fd_;

    void get_info();
    void mode_in(std::uint32_t flags);
    void mode_out(std::uint32_t flags, gpio::state);
    void state(gpio::state);

    std::vector<char> buffer_;
    void sched_read();

    ////////////////////
    using ticks = nsec::rep;
    std::atomic<ticks> high_ticks_, low_ticks_;
    void sync_state();

    std::future<void> pwm_;
    std::atomic<bool> stop_ { false };

    void pwm_start();
    void pwm_stop();
    bool pwm_started() const noexcept { return pwm_.valid(); }
};

////////////////////////////////////////////////////////////////////////////////
}
}

////////////////////////////////////////////////////////////////////////////////
#endif
