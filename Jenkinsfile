pipeline {
  agent any
  triggers {
  pollSCM('H/30 * * * *')
  }
  stages {
    stage('checkout scm') {
      steps {
        git 'eolJenkins:ncar/libraf'
      }
    }
    stage('Build') {
      steps {
        sh 'make '
      }
    }
  }
  post {
    always {
      mail(subject: 'libraf build successful', body: 'libraf build successful', to: 'cjw@ucar.edu taylort@ucar.edu')
    }

  }
  options {
    buildDiscarder(logRotator(numToKeepStr: '10'))
  }
}
