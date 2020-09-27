/*
 * Copyright (C) 2020  Kaputnik Go
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * QTaudio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <QCoreApplication>
#include <QDebug>
#include <QAudio>
#include <QAudioDeviceInfo>
#include <QMediaPlayer>

#include "example.h"
#include "audiogen.h"

using namespace std;

Example::Example() :
  headphoneProcess(),
  speakerProcess(),
  headphoneVolProcess(),
  speakerVolProcess(),
  micMuteProcess(),
  mic1UnmuteProcess(),
  mic2UnmuteProcess(),
  headphoneVolRead('0'),
  speakerVolRead('0'),
  micMutesRead('0'),
  qMediaPlayer(),
  audioGenTest()
{
    connect(&headphoneProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onHeadphoneFinished(int, QProcess::ExitStatus)));
    connect(&speakerProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onSpeakerFinished(int, QProcess::ExitStatus)));
    connect(&headphoneVolProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onHeadphoneVolFinished(int, QProcess::ExitStatus)));
    connect(&speakerVolProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onSpeakerVolFinished(int, QProcess::ExitStatus)));
    connect(&micMuteProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onMicMuteFinished(int, QProcess::ExitStatus)));
    connect(&mic1UnmuteProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onMic1UnmuteFinished(int, QProcess::ExitStatus)));
    connect(&mic2UnmuteProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onMic2UnmuteFinished(int, QProcess::ExitStatus)));
}

// TODO :: cldean up this mess :)

/******************************************************************************/
void Example::speakers() {
    // called from qml button: headphones vol 2%, speakers 85%
    qDebug() << "speakers on";
    // hardcoded location bad ...
    speakerProcess.start("bash /opt/click.ubuntu.com/qtaudio.kaputnikgo/current/scripts/speakers.sh");
    speakerProcess.waitForFinished();
    speakerProcess.close();
    //readSpeakerVol();
}
void Example::readSpeakerVol() {
    qDebug() << "speaker vol read";
    speakerVolProcess.start("bash /opt/click.ubuntu.com/qtaudio.kaputnikgo/current/scripts/speaker_vol.sh");
    speakerVolProcess.waitForFinished();
    speakerVolRead = QString(speakerVolProcess.readAllStandardOutput());
    // strip /n
    speakerVolRead.chop(1);
    speakerVolProcess.close();
    qDebug() << speakerVolRead;
}
QString Example::getSpeakerVol() {
    speakers();
    qDebug() << "getSpeakerVol: " << speakerVolRead;
    qDebug() << "speaker vol read";
    speakerVolProcess.start("bash /opt/click.ubuntu.com/qtaudio.kaputnikgo/current/scripts/speaker_vol.sh");
    speakerVolProcess.waitForFinished();
    speakerVolRead = QString(speakerVolProcess.readAllStandardOutput());
    // strip /n
    speakerVolRead.chop(1);
    speakerVolProcess.close();
    qDebug() << speakerVolRead;
    return speakerVolRead;
}
void Example::setSpeakerVol(const QString &t) {
    // check t i sin range and is number
    if (t != speakerVolRead) {
        speakerVolRead = t;
        emit speakerVolChanged();
    }
}

void Example::onSpeakerFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "Speaker on finished";
    qDebug() << "exit code" << exitCode << "exit status" << exitStatus;
}
void Example::onSpeakerVolFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "Speaker Vol read finished";
    qDebug() << "exit code" << exitCode << "exit status" << exitStatus;
}

/******************************************************************************/

void Example::headphones() {
    // called from qml button: unmute headphones vol 85%, speakers 2%.
    qDebug() << "headphones on";
    // hardcode location bad...
    headphoneProcess.start("bash /opt/click.ubuntu.com/qtaudio.kaputnikgo/current/scripts/headphones.sh");
    headphoneProcess.waitForFinished();
    headphoneProcess.close();
    //readHeadphoneVol();
}
void Example::readHeadphoneVol() {
    qDebug() << "headphone vol read";
    headphoneVolProcess.start("bash /opt/click.ubuntu.com/qtaudio.kaputnikgo/current/scripts/headphone_vol.sh");
    headphoneVolProcess.waitForFinished();
    headphoneVolRead = QString(headphoneVolProcess.readAllStandardOutput());
    // strip /n
    headphoneVolRead.chop(1);
    headphoneVolProcess.close();
    qDebug() << headphoneVolRead;
}
QString Example::getHeadphoneVol() {
    headphones();
    qDebug() << "getHeadphoneVol: " << headphoneVolRead;
    qDebug() << "headphone vol read";
    headphoneVolProcess.start("bash /opt/click.ubuntu.com/qtaudio.kaputnikgo/current/scripts/headphone_vol.sh");
    headphoneVolProcess.waitForFinished();
    headphoneVolRead = QString(headphoneVolProcess.readAllStandardOutput());
    // strip /n
    headphoneVolRead.chop(1);
    headphoneVolProcess.close();
    qDebug() << headphoneVolRead;
    return headphoneVolRead;
}
void Example::setHeadphoneVol(const QString &t) {
    // check t is in range and is number
    if (t != headphoneVolRead) {
        headphoneVolRead = t;
        emit headphoneVolChanged();
    }
}

void Example::onHeadphoneFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "Headphone on finished";
    qDebug() << "exit code" << exitCode << "exit status" << exitStatus;
}
void Example::onHeadphoneVolFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "Headphone Vol read finished";
    qDebug() << "exit code" << exitCode << "exit status" << exitStatus;
}

/******************************************************************************/

// mute all
void Example::micMute() {
    qDebug() << "Mic mute called.";
    micMuteProcess.start("bash /opt/click.ubuntu.com/qtaudio.kaputnikgo/current/scripts/mic_mute.sh");
    micMuteProcess.waitForFinished();
    micMuteProcess.close();
    qDebug() << "Mic mute process closed.";
}
void Example::onMicMuteFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "Mic mute on finished";
    qDebug() << "exit code" << exitCode << "exit status" << exitStatus;
}
// MIC 1
void Example::mic1Unmute() {
    qDebug() << "Mic1 unmute called.";
    micMuteProcess.start("bash /opt/click.ubuntu.com/qtaudio.kaputnikgo/current/scripts/mic1_unmute.sh");
    micMuteProcess.waitForFinished();
    micMuteProcess.close();
    qDebug() << "Mic1 unmute process closed.";
}
void Example::onMic1UnmuteFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "Mic1 unmute on finished";
    qDebug() << "exit code" << exitCode << "exit status" << exitStatus;
}
// MIC 2
void Example::mic2Unmute() {
    qDebug() << "Mic2 unmute called.";
    micMuteProcess.start("bash /opt/click.ubuntu.com/qtaudio.kaputnikgo/current/scripts/mic2_unmute.sh");
    micMuteProcess.waitForFinished();
    micMuteProcess.close();
    qDebug() << "Mic2 unmute process closed.";
}
void Example::onMic2UnmuteFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    qDebug() << "Mic2 unmute on finished";
    qDebug() << "exit code" << exitCode << "exit status" << exitStatus;
}
/******************************************************************************/

void Example::audioSetup() {
    qDebug() << "audioSetup get device info:";
    const auto deviceInfos = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

    for (const QAudioDeviceInfo &deviceInfo : deviceInfos) {
      qDebug() << "Device name: " << deviceInfo.deviceName();
    }
/*
prints:
      audioSetup get device info:
      Device name:  "default"
      Device name:  "pulse"
      Device name:  "sysdefault:CARD=sun50ia64audio"
      Device name:  "dmix:CARD=sun50ia64audio,DEV=0"
      Device name:  "dsnoop:CARD=sun50ia64audio,DEV=0"
      Device name:  "hw:CARD=sun50ia64audio,DEV=0"
      Device name:  "plughw:CARD=sun50ia64audio,DEV=0"
      Device name:  "alsa_output.platform-sound.HiFi__hw_sun50ia64audio__sink"
      Device name:  "sink.fake.sco"
*/
    // test the QMediaPlayer object with current return values in rem
    // no media is loaded so values will reflect a default state
    qDebug() << "qmediaplayer invoke";
    qDebug() << "isAudioAvailable: " << qMediaPlayer.isAudioAvailable(); // false
    qDebug() << "current state: " << qMediaPlayer.state(); // StoppedState
    qDebug() << "media status: " << qMediaPlayer.mediaStatus(); // NoMedia
    qDebug() << "audio role: " << qMediaPlayer.audioRole(); // MusicRole
    // looks for "file://" + "yourfileyouwanttoplay.mp3"
    qMediaPlayer.setMedia(QUrl::fromLocalFile(QStringLiteral("/opt/click.ubuntu.com/qtaudio.kaputnikgo/current/assets/AlicePt1.ogg"))); // working
}
void Example::playAlice() {
    // check for qMediaPlayer.mediaStatus() == QMediaPlayer::LoadedMedia
    qDebug() << "playAlice called, status: " << qMediaPlayer.mediaStatus(); // returns loadingMedia
    if (qMediaPlayer.mediaStatus() == QMediaPlayer::LoadingMedia) {
        qDebug() << "Check: Alice is loading, try play.";
        // default vol = 100, set volume to 50, not logarithmic
        if (qMediaPlayer.volume() == 100) {
            qMediaPlayer.setVolume(50);
        }
        qMediaPlayer.play();
    }
    else {
        qDebug() << "Check: Alice not loading: " << qMediaPlayer.mediaStatus();
    }
}
void Example::stopAlice() {
    qDebug() << "stopAlice called, status: " << qMediaPlayer.mediaStatus(); // returns
    qMediaPlayer.stop();
}

/******************************************************************************/

void Example::runAudioGen() {
    qDebug() << "runAudioGen called from qml";
    //AudioTest audioGenTest;
    audioGenTest.runAudioGenTest();
}
void Example::toggleAudioGen() {
    qDebug() << "toggleAudioGen called from qml";
    audioGenTest.toggleSuspendResume();
}


/******************************************************************************/

void Example::destructor() {
    // try and catch app close/exit/destroy etc - DOES NOT
    qDebug() << "DESTRUCTOR CALLED.";
}
