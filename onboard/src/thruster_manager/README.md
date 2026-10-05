# `thruster_manager`

## What is it?
This package converts the "percentage" values of each thruster into a PWM for each thruster. It receives from `gamepad_interpreter` a list of eight percentages, each represented as a value between -1 and 1. -1 is full reverse, and 1 is full forwards. It converts all of these values into PWM values, where 1100 to 1500 is reverse (with 1100 as full reverse) and 1500 to 1900 is forwards (where 1900 is full forwards). It then outputs these values, which are read by `pico_interface`. It supports configurable power limits via a ROS2 topic, with a single number defining the relative offset.

## How do I use it?
**{TODO add launch instructions}**

To configure the thruster PWM limit, publish a single number to the thruster_percents topic. This represents the relative offset from maximum power. On startup, this value defaults to 200, so the lower limit is 1300 (1100 + 200) and the upper limit is 1700 (1900 - 200). Attempting to set a limit offset less than 0 or greater than 400 is ignored and instead sets the limit to either 0 or 400, respectively.

## What topics/services/actions does the package use for input? **{TODO add more inputs as needed}**
- Topics:
    - `thruster_percents` : power percentage values for each thruster
    - `gamepad_interpreter_heartbeat`: heartbeat from the `gamepad_interpreter` node

## What topics/services/actions does the package use for output? **{TODO add more outputs as needed}**
- Topics:
    - `topic_name` **{TODO agree on a topic name with the pico_interface team}**: PWM values for each thruster
    - `thruster_manager_heartbeat`: heartbeat for this package

## What custom message types or libraries does the package use?
None **{TODO add as needed (you'll likely end up with a custom message type for both thruster percentage and thruster power values. Agree on these with the relevant teams that will also use the message.)}**
