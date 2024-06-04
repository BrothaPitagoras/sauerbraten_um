#include "structs/Matrix.hpp"


bool Matrix::WorldToScreen(Vector3 worldPos, int width, int height, Vector2& screenPos) {

    //multiply vector against matrix
    float screenX = (m11 * worldPos.x) + (m21 * worldPos.y) + (m31 * worldPos.z) + m41;
    float screenY = (m12 * worldPos.x) + (m22 * worldPos.y) + (m32 * worldPos.z) + m42;
    float screenW = (m14 * worldPos.x) + (m24 * worldPos.y) + (m34 * worldPos.z) + m44;

    //camera position (eye level/middle of screen)
    float camX = width / 2.0f;
    float camY = height / 2.0f;

    //convert to homogeneous position
    float x = camX + (camX * screenX / screenW);
    float y = camY - (camY * screenY / screenW);
    screenPos = Vector2(x, y);

    //check if object is behind camera / off screen (not visible)
    //w = z where z is relative to the camera 
    return (screenW > 0.001f);
}