/*
  processaudio.js
  Audio Processing Script for nodejs
  MIT Licensed (C) 2016 Richard Marks <ccpsceo@gmail.com>
  
  Usage:
  
  First install FFMpeg with brew

  brew install ffmpeg --with-fdk-aac --with-ffplay --with-freetype --with-libass --with-libquvi --with-libvorbis --with-libvpx --with-opus --with-x265

  then run node processaudio.js yourfilenamehere.wav anoptionalfilenamehere.wav
  and you will get back an mp3, an ogg, and an m4a audio file for each subsequent wav
  provided there are no errors.
*/
'use strict';

const path = require('path');
const exec = require('child_process').exec;

const tool = {
  processAudio(filename) {
    return new Promise((resolve, reject) => {
      const command = tool._buildAudioProcessingCommand(filename);
      exec(command, (err, stdout, stderr) => {
        if (err) { return reject({
          filename,
          err,
        }); }
        return resolve({
          filename,
          stdout,
          stderr,
        });
      });
    });
  },
  _buildAudioProcessingCommand(filename) {
    const command = [];
    command.push('ffmpeg -y -channel_layout FC -i');
    command.push(filename);
    // command.push('-acodec libmp3lame -ab 64k');
    // command.push(tool._replaceExtension(filename, 'mp3'));
    command.push('-acodec libvorbis -qscale:a 2');
    command.push(tool._replaceExtension(filename, 'ogg'));
    // command.push('-acodec libfdk_aac -b:a 64k');
    // command.push(tool._replaceExtension(filename, 'm4a'));
    return command.join(' ');
  },
  _replaceExtension(filename, extension) {
    const ext = path.extname(filename);
    const replaced = filename.replace(ext, `.${extension}`);
    return replaced;
  },
};

function onSuccess(result) {
  console.log(`Processed ${result.filename}`);
  console.log(`${result.stdout}`);
  console.log(`${result.stderr}`);
}

function onFailure(result) {
  console.log(`Failed to process ${result.filename}`);
  console.error(result.err);
}

function main(argc, argv) {
  if (argc < 3) {
    console.error('Missing required parameter <filename>\nnode processaudio.js <filename>');
    return process.exit(1);
  }
  for (let i = 2; i < argc; i += 1) {
    const filename = argv[i];
    console.log(`Processing ${filename}`);
    tool.processAudio(filename).then(onSuccess).catch(onFailure);
  }
}

main(process.argv.length, process.argv);