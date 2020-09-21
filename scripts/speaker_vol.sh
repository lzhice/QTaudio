#!/bin/bash
# get Speakers (Line Out) volume for Left channel, assuming as mono

set -e

get_volume()
{
    mixer=$(amixer sget 'Line Out' | grep 'Front Left:')
    echo $mixer | awk -F"Left:|[][]" '/dB/ { print $3 }'
}

vol=$(get_volume | grep -o -E '[0-9]+')
# ie, will echo number only, not % sign: 75
echo "$vol"
