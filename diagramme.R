#=========================================================
#=============== PROJET DE C++ ===========================
#=========================================================

par(mfrow=c(1,1))


stat_bact =read.table('BactT950A5.txt')
time = stat_bact[,1]
A = stat_bact[,2]
B = stat_bact[,3]
plot(time,A,lty=1,lwd=1,col=2,type="l",ylim=c(0,1025))
lines(time,B,col=3)
abline(v=0)
abline(h=0)

#========================= DIAGRAMME DE PHASE =============================

Graph = read.table('DataPPhase.txt', header = T)
plot(Graph$T,Graph$A_init,col=Graph$Code+1,pch=19,xlab="T",ylab="Ainit",
     main="Diagramme de Phase 
     (Exclusion: Vert, Extinction: Noir, Cohabitation: Rouge")


