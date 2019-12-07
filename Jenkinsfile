pipeline {
  agent {
    kubernetes {
        //cloud 'kubernetes'
        containerTemplate {
          name 'stpad'
          image 'vookimedlo/ubuntu-qt:5.12_clang_bionic'
          ttyEnabled true
       }
    }
  }
  stages {
    stage('Pre-Build') {
      steps {
        sh 'echo Hello World'
        sh 'ls'
      }
    }
    stage('Build') {
      steps {
        sh 'qmake src/STPad.pro'
      }
    }
  }
}
