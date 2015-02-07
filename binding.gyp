{
  'targets': [
    {
      'target_name': 'node_sleep',
      'sources': [
        'sleep.cc',
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
