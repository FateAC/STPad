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
        sh 'echo Hello World'
        sh 'ls'
      }
    }
  }
}
