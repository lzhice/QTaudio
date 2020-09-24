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

#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QObject>
#include <QProcess>

class Example: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString headphoneVolRead READ getHeadphoneVol WRITE setHeadphoneVol NOTIFY headphoneVolChanged)
    Q_PROPERTY(QString speakerVolRead READ getSpeakerVol WRITE setSpeakerVol NOTIFY speakerVolChanged)
    Q_PROPERTY(QString micMutesRead READ getMicMutes WRITE setMicMutes NOTIFY micMutesChanged)

  public:
    Example();
    ~Example() = default;

    Q_INVOKABLE void headphones();
    Q_INVOKABLE void readHeadphoneVol();
    Q_INVOKABLE QString getHeadphoneVol();

    Q_INVOKABLE void speakers();
    Q_INVOKABLE void readSpeakerVol();
    Q_INVOKABLE QString getSpeakerVol();

    Q_INVOKABLE void micMute();
    Q_INVOKABLE void mic1Unmute();
    Q_INVOKABLE void mic2Unmute();
    Q_INVOKABLE QString getMicMutes();

    Q_INVOKABLE void audioHijack();

    void setHeadphoneVol(const QString &t);
    void setSpeakerVol(const QString &t);
    void setMicMutes(const QString &t);

  private Q_SLOTS:
    void onHeadphoneFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onSpeakerFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onHeadphoneVolFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onSpeakerVolFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onMicMuteFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onMic1UnmuteFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onMic2UnmuteFinished(int exitCode, QProcess::ExitStatus exitStatus);

  signals:
    void headphoneVolChanged();
    void speakerVolChanged();
    void micMutesChanged();

  private:
    QProcess headphoneProcess;
    QProcess speakerProcess;
    QProcess headphoneVolProcess;
    QProcess speakerVolProcess;
    QProcess micMuteProcess;
    QProcess mic1UnmuteProcess;
    QProcess mic2UnmuteProcess;

    QString headphoneVolRead;
    QString speakerVolRead;
    QString micMutesRead;

};

#endif
