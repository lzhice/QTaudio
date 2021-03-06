/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef AUDIOGEN_H
#define AUDIOGEN_H

#include <math.h>
#include <QAudioOutput>
#include <QAudioInput>
#include <QByteArray>
#include <QIODevice>
#include <QObject>
#include <QTimer>
#include <QFile>
/*
#include <QComboBox> // no
#include <QLabel> // no
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
*/


// UI part of this needs to be in a QML file...

class Generator : public QIODevice {
      Q_OBJECT

  public:
      Generator(const QAudioFormat &format, qint64 durationUs, int sampleRate, QObject *parent);
      ~Generator();

      void start();
      void stop();

      qint64 readData(char *data, qint64 maxlen);
      qint64 writeData(const char *data, qint64 len);
      qint64 bytesAvailable() const;

  private:
      void generateData(const QAudioFormat &format, qint64 durationUs, int sampleRate);

  private:
      qint64 m_pos;
      QByteArray m_buffer;
};


/*************************************************************************/

class AudioGenTest: public QObject {
      Q_OBJECT

  public:
      AudioGenTest();
      ~AudioGenTest();

      void runAudioGenTest();
      void toggleSuspendResume();
      int getCurrentToneFreq();
      void testAudioInput();

  private:
      //void initializeWindow(); // THIS TO GO
      void initializeAudio();
      void createAudioOutput();

  private:
      QTimer *m_pushTimer;
      int ToneSampleRateHz;

      // Owned by layout
      /*
      QPushButton *m_modeButton;
      QPushButton *m_suspendResumeButton;
      QComboBox *m_deviceBox;
      QLabel *m_volumeLabel;
      QSlider *m_volumeSlider;
      */

      QAudioDeviceInfo m_deviceInfo;
      QAudioDeviceInfo m_deviceInfoIn;
      Generator *m_generator;
      QAudioOutput *m_audioOutput;
      QAudioInput *m_audioInput;
      QIODevice *m_outputDevice; // not owned
      QAudioFormat m_formatOut;
      QAudioFormat m_formatIn;
      QFile destinationFile;

      bool m_pullMode;
      QByteArray m_buffer;

  private slots:
      void pushTimerExpired();
      void toggleMode();
      void deviceChanged(int index);
      void volumeChanged(int);
      void stopRecording();
};

#endif // AUDIOGEN_H
