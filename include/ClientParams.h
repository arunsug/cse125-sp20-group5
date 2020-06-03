#ifndef _CLIENT_PARAMS_H
#define _CLIENT_PARAMS_H

class ClientParams {
public:

    //Sound
    float BGMVolume;

    // Scaler
    float seedSourceScaler;
    float dirtScaler;
    float treeScaler;
    float stoneScaler;

    // Camera
    float FOV;
    float aspect;
    float nearClip;
    float farClip;
    float distance;
    float azimuth;
    float incline;


    ClientParams();

};
#endif