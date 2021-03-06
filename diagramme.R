#=========================================================
#=============== PROJET DE C++ ===========================
#=========================================================

par(mfrow=c(2,1))


stat_bact =read.table('BactT850A10.txt')
time = stat_bact[,1]
A = stat_bact[,2]
B = stat_bact[,3]
plot(time,A,lty=1,lwd=1,col=2,type="l",ylim=c(0,1025),xlim=c(0,6000))
lines(time,B,col=3)
abline(v=0)
abline(h=0)

conc_stat = read.table("ConcentrationsBactT850A10.txt",header = T)
plot(conc_stat[,1],conc_stat[,3],type="l",ylim =c(0,1),xlim=c(500,1000))
lines(conc_stat[,1],conc_stat[,4],type="l",col=2)
lines(conc_stat[,1],conc_stat[,7],type="l",col=3)
lines(conc_stat[,1],conc_stat[,4],type="l",col=4)

fitnessA = conc_stat$Bbact/stat_bact$V2
fitnessB = conc_stat$Cbact/stat_bact$V3

plot(conc_stat$t,fitnessA,type="l",ylim=c(0,0.001),col=2,xlim=c(0,6000))
lines(conc_stat$t,fitnessB,type="l",col=3)


#========================= DIAGRAMME DE PHASE =============================

Graph = read.table('D01.txt', header = T)
plot(Graph$T,Graph$A_init,col=Graph$Code+1,pch=15,xlab="T",ylab="Ainit",
     main="Diagramme de Phase sans mutation D = 0.1
     Exclusion: Vert, Cohabitation: Rouge, Extinction: Noir")
x=seq(0,1500,250)
axis(1,at=x)

Graph = read.table('MutationD01.txt', header = T)
plot(Graph$T,Graph$A_init,col=Graph$Code+1,pch=15,xlab="T",ylab="Ainit",
     main="Diagramme de Phase avec mutation D = 0.1
     Exclusion: Vert, Cohabitation: Rouge, Extinction: Noir")
x=seq(0,1500,250)
axis(1,at=x)

Graph = read.table('D0.txt', header = T)
plot(Graph$T,Graph$A_init,col=Graph$Code+1,pch=15,xlab="T",ylab="Ainit",
     main="Diagramme de Phase avec un taux de diffusion D = 0
     Exclusion: Vert, Cohabitation: Rouge, Extinction: Noir")
x=seq(0,1500,250)
axis(1,at=x)

Graph = read.table('D002.txt', header = T)
plot(Graph$T,Graph$A_init,col=Graph$Code+1,pch=15,xlab="T",ylab="Ainit",
     main="Diagramme de Phase avec un taux de diffusion D = 0.02
     Exclusion: Vert, Cohabitation: Rouge, Extinction: Noir")
x=seq(0,1500,250)
axis(1,at=x)

Graph = read.table('D0001.txt', header = T)
plot(Graph$T,Graph$A_init,col=Graph$Code+1,pch=15,xlab="T",ylab="Ainit",
     main="Diagramme de Phase D = 0.001
     Exclusion: Vert, Cohabitation: Rouge, Extinction: Noir")
x=seq(0,1500,250)
axis(1,at=x)

Graph = read.table('D000001.txt', header = T)
plot(Graph$T,Graph$A_init,col=Graph$Code+1,pch=15,xlab="T",ylab="Ainit",
     main="Diagramme de Phase D = 0.00001
     Exclusion: Vert, Cohabitation: Rouge, Extinction: Noir")
x=seq(0,1500,250)
axis(1,at=x)

Graph = read.table('D000001.txt', header = T)
plot(Graph$T,Graph$A_init,col=Graph$Code+1,pch=15,xlab="T",ylab="Ainit",
     main="Diagramme de Phase D = 0.00001
     Exclusion: Vert, Cohabitation: Rouge, Extinction: Noir")
x=seq(0,1500,250)
axis(1,at=x)