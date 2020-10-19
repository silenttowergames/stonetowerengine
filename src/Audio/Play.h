#pragma once

typedef enum Play
{
    // Default just does IfAvailable
    Play_Default,
    // BROKEN: Play if there are less than 4 sounds currently playing
    Play_IfAvailable,
    // If none are available, stop one of the SFX
    Play_StopOne,
    // Stop all SFX of this type & play this one
    Play_StopAll,
} Play;

// TODO: When a SFX stops, move all array elements after it back, so the first elements in the array are the oldest
