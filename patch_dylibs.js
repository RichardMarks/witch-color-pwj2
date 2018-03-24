#!/usr/bin/env node
'use strict'

const fs = require('fs')
const path = require('path')
const exec = require('child_process').exec

function doesExist (filename, callback) {
  if (!filename || typeof filename !== 'string' || !filename.length) {
    callback && callback(false)
  } else {
    const mode = fs.constants.F_OK | fs.constants.R_OK
    fs.access(filename, mode, err => {
      if (err) {
        console.error(err)
        callback && callback(false)
      } else {
        callback && callback(true)
      }
    })
  }
}

function otool (filename, callback) {
  const excludeSelf = str => !(str.endsWith(':') || str.startsWith(filename) || str.endsWith(filename))
  const excludeSystem = str => !(str.startsWith('/System/Library/') || str.startsWith('/usr/lib/'))
  const stripWhitespace = str => str.replace(/\s+/g, '')
  const onlyFilename = str => str.split(' ')[0]

  doesExist(filename, fileExists => {
    if (fileExists) {
      const commandLine = `otool -L ${filename}`
      exec(commandLine, (err, stdout, stderr) => {
        if (err) {
          throw err
        } else if (stderr.length) {
          throw new Error(stderr)
        } else {
          const lines = stdout
            .split('\n')
            .filter(Boolean)
            .map(onlyFilename)
            .map(stripWhitespace)
            .filter(excludeSelf)
            .filter(excludeSystem)
          callback && callback(lines)
        }
      })
    } else {
      process.stderr.write(`Error running otool(): File not found or is not accessible by this process.\nFile: ${filename}\n`)
      callback && callback([])
    }
  })
}

const nextTask = (tasks, done) => {
  const task = tasks.shift()
  if (task) {
    // console.log(`Running task: ${task.name}...`)
    task.run && task.run(() => nextTask(tasks, done))
  } else {
    done && done()
  }
}

// install_name_tool -change /usr/local/opt/libvorbis/lib/libvorbis.0.dylib @executable_path/libvorbis.0.dylib ./dmg/WitchColorJamEdition.app/Contents/MacOS/libSDL2_mixer-2.0.0.dylib

function printInstallNameToolCommand (filename, dependency) {
  console.log(`install_name_tool -change ${dependency} @executable_path/${path.basename(dependency)} \$EXEC_DIR/${path.basename(filename)}`)
}

const tasks = []
function createOtoolTask (filename, deps) {
  const task = {
    name: `get dylibs of ${filename}`,
    run (done) {
      if (filename in deps) {
        // console.log(`${filename} already in deps\n`)
        done && done()
      } else {
        otool(filename, dylibs => {
          // console.log(`otool found ${dylibs.length} dylib file${dylibs.length !== 1 ? 's' : ''} as a dependency of ${filename}\n`)
          deps[filename] = dylibs
          dylibs.forEach(dylib => {
            printInstallNameToolCommand(filename, dylib)
            tasks.push(createOtoolTask(dylib, deps))
          })
          done && done()
        })
      }
    }
  }
  return task
}

const deps = {}

tasks.push(createOtoolTask('/Users/rmarks/code/witch-color-wj2/bin/witch-color', deps))
tasks.push(createOtoolTask('/usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib', deps))
tasks.push(createOtoolTask('/usr/local/opt/sdl2_mixer/lib/libSDL2_mixer-2.0.0.dylib', deps))
tasks.push(createOtoolTask('/usr/local/opt/sdl2_image/lib/libSDL2_image-2.0.0.dylib', deps))
tasks.push(createOtoolTask('/usr/local/opt/sdl2_ttf/lib/libSDL2_ttf-2.0.0.dylib', deps))
tasks.push(createOtoolTask('/usr/local/opt/sdl2_ttf/lib/libSDL2_ttf-2.0.0.dylib', deps))

nextTask(tasks, () => {
  console.log('Done.')
  console.log(JSON.stringify(deps, null, 2))
  // Object.keys(deps).forEach(key => console.log(key))
})
