Pod::Spec.new do |s|
  s.name         = "FMDBOrmHandler"
  s.version      = "0.0.1"
  s.summary      = "A short description of FMDBOrmHandler."
  s.homepage     = "https://github.com/caohuan346/FMDBOrmHandler"
  s.license      = "MIT"
  s.author       = { "Happy" => "835965147@qq.com" }
  s.source       = { :git => "https://github.com/caohuan346/FMDBOrmHandler.git", :tag => "0.0.1" }
  s.source_files = "Classes", "src/FMDBOrmHandler/*.{h,m}"
  s.dependency "FMDB"
  s.dependency "GHUnit"
  s.requires_arc = true	
end
