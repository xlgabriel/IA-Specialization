class baseconfig {
  exec { 'apt-get update':
    command => '/usr/bin/apt-get update';
  }

  package { ['apache2', 'tree']:
    ensure => present;
  }

  file { '/var/www/html/index.html':
    ensure  => present,
    owner   => 'root',
    group   => 'root',
    mode    => '0644',
    source => 'puppet:///modules/baseconfig/index.html',
    path    => '/var/www/html/index.html';
  }
  service { "apache2":
    ensure => running,
    enable => true,
    require => Package['apache2'];
  }

}
