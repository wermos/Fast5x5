library(ggplot2)
library(reshape2)
custom_scal = t(read.table("custom_scal.txt", sep=",", skipNul = T)[1:10])
eigen_scal = t(read.table("eigen_scal.txt", sep=",", skipNul = T)[1:10])
matrix_sizes = 3:8

custom_scal = data.frame('Custom', custom_scal)
eigen_scal = data.frame('Eigen', eigen_scal)
colnames(custom_scal) = c('program', matrix_sizes)
colnames(eigen_scal) = c('program', matrix_sizes)

measures = rbind(melt(custom_scal), melt(eigen_scal))

linear_scal = mean(custom_scal$`3`)/9*(3:8)**2

ggplot(measures, aes(variable, value, group=program, color=program)) +
  geom_smooth(se = FALSE) +
  geom_point() +
  xlab("Matrix Size") +
  ylab("Time (s)") +
  ggtitle("Custom implementation vs Eigen time comparison (2e8 matrix multiplications)") +
  theme_minimal()

ggplot(measures, aes(as.numeric(levels(variable))[variable]**2, value, group=program, color=program)) +
  geom_smooth(se = FALSE) +
  geom_point() +
  xlab("Number of elements") +
  ylab("Time (s)") +
  ggtitle("Custom implementation vs Eigen time comparison (2e8 matrix multiplications)") +
  theme_minimal()

speedup = colMeans(eigen_scal[2:7])/colMeans(custom_scal[2:7])

ggplot(stack(speedup), aes(ind, values)) +
  geom_bar(stat="identity") +
  xlab("Matrix Size") +
  ylab("Speedup (Eigen time / Custom time)") +
  ggtitle("Custom implementation vs Eigen speedup") +
  theme_minimal() +
  geom_hline(yintercept=1, color="red") +
  geom_text(aes(ind, values + 0.2, label=round(values, digits=1)))


ggplot(measures, aes(as.numeric(levels(variable))[variable]**2, value/(as.numeric(levels(variable))[variable]**2), group=program, color=program)) +
  geom_smooth(se = FALSE) +
  geom_point() +
  xlab("Number of elements") +
  ylab("Time per element (s)") +
  ggtitle("Custom implementation vs Eigen time per element comparison") +
  theme_minimal()