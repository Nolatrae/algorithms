from matplotlib import pyplot as plt

cpp = {"quantity": [], "size": [], "time": []}
py = {"quantity": [], "size": [], "time": []}

with open ('infoCpp.txt') as infoCpp:
    for line in infoCpp:
      line = list(map(int, line.split()))
      cpp["quantity"] += [line[0]]
      cpp["size"] += [line[1]]
      cpp["time"] += [line[2]]

with open ('infoPy.txt') as infoPy:
    for line in infoPy:
      line = list(map(int, line.split()))
      py["quantity"] += [line[0]]
      py["size"] += [line[1]]
      py["time"] += [line[2]]


plt.figure(figsize=(11,5))

ax = plt.subplot(1, 2, 1)
plt.title("график зависимости требуемого объема памяти")
plt.xlabel("Количество элементов")
plt.ylabel("Размер 'Байт'")
plt.plot(cpp["quantity"], cpp["size"], label="C++")
plt.plot(py["quantity"], py["size"], label="Python")
ax.set_xscale("log")
ax.set_yscale("log")
plt.grid()
plt.legend()

ax = plt.subplot(1, 2, 2)
plt.title("график зависимости скорости выполнения")
plt.xlabel("Количество элементов")
plt.ylabel("Время выполнения(миллисекунды)")
plt.plot(cpp["quantity"], cpp["time"], label="C++")
plt.plot(py["quantity"], py["time"], label="Python")
ax.set_xscale("log")
ax.set_yscale("log")
plt.grid()
plt.legend()


plt.show()