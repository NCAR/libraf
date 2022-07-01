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
    failure {
      emailext to: "cjw@ucar.edu janine@ucar.edu cdewerd@ucar.edu taylort@ucar.edu",
      subject: "Jenkinsfile libraf build failed",
      body: "See console output attached",
      attachLog: true
    }
  }
  options {
    buildDiscarder(logRotator(numToKeepStr: '10'))
  }
}
