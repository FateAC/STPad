pipeline {
  agent {
    kubernetes {
        //cloud 'kubernetes'
        containerTemplate {
          name 'stpad'
          image 'ubuntu:18.04'
          ttyEnabled true
       }
    }
  }
  stages {
    stage('Pre-Build') {
      steps {
        sh 'apt update && apt upgrade -y && apt install wget build-essential libfontconfig1 mesa-common-dev libglu1-mesa-dev -y'
        sh 'cd /tmp'
        sh 'wget https://download.qt.io/official_releases/qt/5.13/5.13.2/qt-opensource-linux-x64-5.13.2.run'
        sh 'chmod +x qt-opensource-linux-x64-5.13.2.run'
        sh './qt-opensource-linux-x64-5.13.2.run'
      }
    }
    stage('Build') {
      steps {
        sh 'qmake src/STPad.pro'
      }
    }
  }
}
