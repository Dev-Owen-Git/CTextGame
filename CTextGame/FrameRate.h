#pragma once

extern double FixedTimeDelta;

void InitFrameRate(const unsigned int FPS);

bool FrameSkip();
void WaitforFrame();

int FrameProcess();
int FrameRender();