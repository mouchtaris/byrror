require 'pry'
require 'json'
require 'pp'
require 'hashie'

json = (JSON.parse File.read 'compile_commands.json').map(&Hashie::Mash.method(:new))
pp json
