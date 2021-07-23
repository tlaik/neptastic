#pragma once

void getNepWindow();
void computeSettings();
bool rgbaToRgb(int width, int height, unsigned char* data);
void printGlErrors();
bool checkSize(GLsizei w, GLsizei h);
bool checkIsBloom(GLsizei w, GLsizei h);
void setBloomSize(GLsizei* w, GLsizei* h);
bool checkIsShadow(GLsizei w, GLsizei h);
void fpsUnlock();