pipeline {
  agent {
    kubernetes {
        //cloud 'kubernetes'
        containerTemplate {
          name 'stpad'
          image 'mcr.microsoft.com/windows:1903'
          ttyEnabled true
       }
    }
  }
  stages {
    stage('Pre-Build') {
      steps {
        sh 'echo Hello World'
        sh 'dir'
      }
    }
  }
}
