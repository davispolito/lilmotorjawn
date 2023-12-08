/*
  ==============================================================================

    utils.h
    Created: 14 Jul 2023 11:33:09am
    Author:  Davis Polito

  ==============================================================================
*/

#pragma once
//borrowed from vital


const ValueDetails ValueDetailsLookup::parameter_list[] = {
   { "", 0x000000, 0.0, 1.0, 0.0, 0.0, 60.0,
     ValueDetails::kLinear, false, "", "Bypass", nullptr },
   { "beats_per_minute", 0x000000, 0.333333333, 5.0, 2.0, 0.0, 60.0,
     ValueDetails::kLinear, false, "", "Beats Per Minute", nullptr },
