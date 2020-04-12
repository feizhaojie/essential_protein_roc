data<-read.csv("C:\\Users\\Administrator\\Desktop\\使用R语言做ROC曲线\\处理\\DC\\DC.csv",head = T,sep = ',')
head(data,6)
#计算各种绘图曲线所需指标
result<-data.frame(pre_prob = data$predictions,true_label = data$lables)
result<-result[order(result$pre_prob,decreasing = T),]
result$cumsum<-cumsum(rep(1,nrow(result)))#计算累计样本个数
result$poscumsum<-cumsum(result$true_label)#计算累计正样本数
result$tpr <- round(result$poscumsum/sum(result$true_label),3) #计算真正率tpr
result$fpr<-round((result$cumsum-result$poscumsum)/sum(result$true_label == 0),3)#计算假正率fpr
result$lift <-round((result$poscumsum/result$cumsum)/sum(result$true_label/nrow(result)),3)#计算提升率lift

#接下来绘制ROC曲线，KS，LIFT曲线
#利用plot函数绘制各种曲线
#ROC曲线
plot(x = result$fpr,y = result$tpr,type = "l",main = "利用plot函数绘制ROC曲线",
      xlab = "False Postive Rate",ylab = "True Postive Rate")
abline(a = 0,b = 1,lty = 2,col = "grey")
library(ROCR)
auc <- performance(prediction(result$pre_prob,result$true_label),'auc')@y.values[[1]]
text(0.5,0.4,labels = paste("AUC:",round(auc,3)),col = "red3")
