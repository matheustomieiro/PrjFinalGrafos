nomes = {"Suzana", "Marcos", "Rosana", "Roberto", "Tiago",
	"Mateus", "Felipe", "Ana", "Almir", "Juliana", "Renata",
	"Marcos", "Murilo", "Luciana", "Regina", "Jose", "Leandro",
	"Julia", "Andre", "Camilla", "Maria", "Tereza", "Jonas", "Amadeu",
	"Teodoro", "Sampaio", "Reginaldo", "Pedro", "Michele", "Rick",
	"Annie"}

cores = {"azul", "roxo", "preto", "vermelho", "amarelo",
        "laranja", "verde", "marrom", "cinza", "branco"
}

times = {"sao caetano", "sao paulo", "corinthians", "barcelona",
        "real madrid", "manchester united", "cruzeiro", "brasil",
        "palmeiras", "flamengo"
}

filmes = {"eu sou a lenda", "novica rebelde", "tomates verdes e fritos",
          "kimi no na wa", "sonic", "rocketman", "era do gelo", "shrek",
          "detetive pikachu", "paprika", "senhor dos aneis"
}

cidades = {"sao paulos", "sao carlos", "rio de janeiro", "manaus", "curitiba",
          "salvador", "campinas", "riberao preto", "florianopolis", "rio branco"
}

file = io.open("script.out","w+");
io.output(file)
if arg[1] == nil then
  print("Digite um argumento... (numero de usuarios a serem gerados!)")
  os.exit()
end

io.write("nome" .. "," .. "username" .. "," .. "pin" .. "," .. "idade" .. "," .. 
        "cidade" .. "," .. "filme" .. "," .. "time" .. "," .. "cor\n")

for i=0, arg[1] do
  local nome = nomes[math.random(1,31)]
  local username = "" .. string.lower(nome) .. tostring(i)
  local pin = math.random(1000, 9999)
  local idade = math.random(17,70)
  local cidade = cidades[math.random(1,10)]
  local filme = filmes[math.random(1,10)]
  local time = times[math.random(1,10)]
  local cor = cores[math.random(1,10)]
  io.write(nome .. "," .. username .. "," .. pin .. "," .. idade ..
          "," .. cidade .. "," .. filme .. "," .. time .. "," .. cor .. '\n')
end
io.close(file)
