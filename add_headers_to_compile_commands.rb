require 'pry'
require 'json'
require 'pp'
require 'hashie'

COMPILE_COMMANDS = 'compile_commands.json'

def vstruct
  Struct.new :v
end
CompileCommands = vstruct
Entry = vstruct
Filepath = vstruct
Sourcefile = vstruct
Headerfiles = vstruct
EntryWithSource = vstruct
Str = vstruct
EntriesWithSources = vstruct
Typechecks = {
  CompileCommands => Array,
  Entry => Hashie::Mash,
  Filepath => String,
  Sourcefile => MatchData,
  Headerfiles => Array,
  EntryWithSource => Array,
  Str => String,
  EntriesWithSources => Array
}
def typecheck(class1, obj)
  class2 = Typechecks[class1]
  raise ArgumentError, "no inner classcheck for #{class1}" unless class2
  raise ArgumentError, "#{class1}.#{class2}: #{obj.class} #{obj.v.class} #{obj.inspect}" \
    unless obj.is_a?(class1) && obj.v.is_a?(class2)
  obj.v
end

def compile_commands
  json = (JSON.parse File.read COMPILE_COMMANDS).map(&Hashie::Mash.method(:new))
  CompileCommands.new json.map(&Entry.method(:new))
end

def filepath(entry)
  Filepath.new typecheck(Entry, entry).file
end

SourceFileRx = /src\/(?<fname>.*)\.cpp$/
def sourcefile(file)
  Sourcefile.new SourceFileRx.match typecheck(Filepath, file)
end

def entry_to_headerfiles(entry)
  sf = sourcefile filepath entry
  sf if sf.v
end

def entries_with_sources(compile_commands)
  EntriesWithSources.new typecheck(CompileCommands, compile_commands)
    .map { |e| [e, entry_to_headerfiles(e)] }
    .select { |e, hs| hs }
    .map(&EntryWithSource.method(:new))
end

def each_header(source)
  return enum_for :each_header, source unless block_given?
  md = typecheck(Sourcefile, source)
  %w[ h hpp ].map(& ->(ext) {
    yield "include/#{md[:fname]}.#{ext}"
  })
end

def replace_source_with_header(entry_with_source)
  entryTS, src = typecheck(EntryWithSource, entry_with_source)
  md = typecheck(Sourcefile, src)
  entry = typecheck(Entry, entryTS)
  each_header(src) do |header|
    Entry.new entry.dup.tap { |e|
      e.command = e.command.gsub(md[0], header)
      e.file = e.file.gsub(md[0], header)
    }
  end
end

def augment(compile_commands)
  entries_with_sources(compile_commands).v
    .flat_map(&method(:replace_source_with_header))
    .concat(typecheck(CompileCommands, compile_commands))
    .map { |e| typecheck(Entry, e) }
end

if __FILE__ == $0
  a = augment compile_commands
  File.open(COMPILE_COMMANDS, 'w') { |fout| fout.write JSON.dump a }
end
