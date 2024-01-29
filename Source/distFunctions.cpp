/*
  ==============================================================================

    distFunctions.cpp
    Created: 15 Jan 2024 5:54:27pm
    Author:  Cheka

  ==============================================================================
*/

#include "distFunctions.h"

float distortionFunction(int idx, float channelData,float volume,float cleanSig,float maxVal){
    switch (idx) {
    case 1:
        return ((volume) * (((TWOVERPI) * (atanf(channelData))) + (cleanSig * 0.5)));
    case 2:
        
        return 0;//+ (cleanSig * 0.5));
    case 3:
        return  volume*(((TWOVERPI) * (atanf(channelData)))+ (cleanSig * 0.1));  // 0.3989 term provides flat response
    default:
        return 0;
}


}

float windowFunction(int N,int sample) {
    return (0.5 - (0.5 * cosf((2 * (juce::float_Pi)*sample) / N - 1)));
}





//*channelData *= drive;
//*channelData = ((volume) * (((TWOVERPI) * (atanf(*channelData))) + (cleanSig / 2)));
//*channelData = (volume*(((2.f /(juce::float_Pi)) * (tanf(*channelData)))+(cleanSig/2)));
//*channelData = ((volume+distcontant) * (((PIOVER2) * (atanf(*channelData))) + (cleanSig / 2) - ((sinf((*channelData)/200)) / 2)));
//*channelData = ((volume + distcontant) * (((PIOVER2) * (atanf(*channelData))) + (cleanSig / 2) - ((sinf(*channelData)) / 8)));
//*channelData = ((volume/(s/gain)) * (((PIOVER2) * (atanf(*channelData))) + (cleanSig / 2) - ((sinf(*channelData)) / 8)));
//*channelData = ((volume ) * ((cleanSig / 2) + ((sinf(*channelData * 50)) / 8)));
//*channelData = ((volume +distcontant) * ((cleanSig / 2) + ((sinf(*channelData * 50)) / 8)));
//*channelData = ((volume / 2) * (((PIOVER2) * (atanf(*channelData))) + (cleanSig / 2) - ((sinf(*channelData*(sinf(cleanSig)) * 50)) / 8)));