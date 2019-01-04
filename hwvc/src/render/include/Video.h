/*
* Copyright (c) 2018-present, lmyooyo@gmail.com.
*
* This source code is licensed under the GPL license found in the
* LICENSE file in the root directory of this source tree.
*/
#ifndef HARDWAREVIDEOCODEC_VIDEO_H
#define HARDWAREVIDEOCODEC_VIDEO_H

#include "Unit.h"
#include "TextureAllocator.h"
#include "Decoder.h"
#include "YUV420PFilter.h"
#include "EventPipeline.h"
#include "Egl.h"

enum PlayState {
    PAUSE = 0,
    PLAYING = 1,
    STOP = -1
};

class Video : public Unit {
public:
    Video();

    virtual ~Video();

    virtual void release() override;

    bool eventPrepare(Message *msg);

    bool eventStart(Message *msg);

    bool eventPause(Message *msg);

    bool eventStop(Message *msg);

    bool eventInvalidate(Message *msg);

private:
    EventPipeline *pipeline = nullptr;
    Egl *egl = nullptr;
    TextureAllocator *texAllocator = nullptr;
    Decoder *decoder = nullptr;
    AVFrame *avFrame = nullptr;
    YUV420PFilter *yuvFilter = nullptr;
    GLuint yuv[3];
    PlayState playState = STOP;

    void loop();

    void checkFilter();

    int grab();
};


#endif //HARDWAREVIDEOCODEC_VIDEO_H