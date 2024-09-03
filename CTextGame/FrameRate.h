#pragma once

extern double FixedDeltaTime;

void InitFrameRate(const unsigned int FPS);

bool FrameSkip();
void WaitforFrame();

int FrameProcess();
int FrameRender();