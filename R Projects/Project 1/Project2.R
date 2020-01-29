library("fBasics")
library("TSA")
library("forecast")
library("tidyverse")
library("Metrics")
library("TTR")
library("fUnitRoots")
GLEN = read.csv("GLEN.L.csv",sep=",");
Gprice <- GLEN[,6]; #stock price
Greturns <- log(Gprice[-1] / Gprice[-length(Gprice)]); # log returns 
dt <- seq(as.Date("2013/06/17"), as.Date("2017/02/20"), "weeks");
dtr <- seq(as.Date("2013/06/24"), as.Date("2017/02/20"), "weeks");
GLENa = data.frame(Greturns, dtr) #dataframe for returns
GLENb = data.frame(Gprice,dt)  #datafram for price
# Question 1 ---------------------------------
#Exploratory Analysis

#Testing for stationarity 
t.test(Gprice)
t.test(Greturns)
acf(x)
adfTest(Gprice, type = "c")
adfTest(Greturns, type = "nc")
#Checking for seaosonality 
prd = periodogram(Greturns, main = "Periodogram of the Log Returns")
o = order(-prd$spec);
d = cbind(prd$freq[o],prd$spec[o])
head(d)
1/max(d[1,1]);
#testing for whitenoise
Box.test(Gprice, lag = max(5,log(length(Gprice))), type= "Ljung-Box")
Box.test(Greturns, lag = max(5,log(length(Greturns)),3*2), type= "Ljung-Box")
acf(Greturns)
acf(Gprice)
#Plots
Xg = ggplot(GLENb, aes(x = dt, y = Gprice)) + geom_line() +
  labs(title="Time Series of Glencore plc Stock Price", x="Date", y="Stock Price") +
  scale_x_date(breaks = pretty(dt,n=8),date_labels  = "%Y") +
  scale_y_continuous(breaks = pretty(Gprice,n=8))
Xg
Yg = ggplot(GLENa, aes(x = dtr, y = Greturns)) + geom_line() +
  labs(title="Log Returns of Glencore plc", x="Date", y="Log Returns") +
  scale_x_date(breaks = pretty(dt,n=8),date_labels = "%Y") +
  scale_y_continuous(breaks = pretty(Greturns,n=8))
Yg

#Question 2  ---------------------------------
#AR(p) model analysis
#Order Specification
pacf(Greturns)
ar(Greturns)$aic
#Model Fitting
Arima(Greturns,order = c(4,0,0))  #AIC=-490.76   AICc=-490.3   BIC=-471.21
AR_4 = Arima(Greturns, order = c(4,0,0),fixed = c(0,0,0,NA,0)) 
AR_4$coef
#Model Validation
plot(AR_4$residuals)
acf(AR_4$residuals)
Box.test(AR_4$residuals, lag = max(7,log(length(AR_4$residuals))), fitdf = 2)
tsdiag(AR_4)
#Question 3 ---------------------------------
#ARMA(p,q) model analysis 
#Order Specification
t = eacf(Greturns)
t
t$eacf

#Model Fittings
Arima(Greturns, order = c(3,0,2))
ARMA_43 = Arima(Greturns, order = c(4,0,3),
                fixed = c(NA,0,NA,NA,NA,0,NA,0)) 
ARMA_22 = Arima(Greturns, order = c(2,0,2),
                fixed = c(0,NA,0,NA,0)) 
ARMA_11 = Arima(Greturns, order = c(1,0,1),
                include.mean = FALSE)
#Model Validation
Box.test(ARMA_43$residuals,lag = max(9,log(length(ARMA_43$residuals))), fitdf = 4)
Box.test(ARMA_22$residuals, lag = max(7,log(length(ARMA_22$residuals))), fitdf = 2)
Box.test(ARMA_11$residuals, lag = max(7,log(length(ARMA_22$residuals))), fitdf = 2)
tsdiag(ARMA_22)

#Comparing AR(4) and ARMA(2,2)
x = Greturns
#Radjusted
1-sum(AR_4$residuals^2)/sum((x-mean(x))^2)*(length(x)-1)/( length(x)-1-1)
1-sum(ARMA_22$residuals^2)/sum((x-mean(x))^2)*(length(x)-1-1)/( length(x)-2-1)
rmse(x,AR_4$fitted)
rmse(x, ARMA_22$fitted)

#P-optimal EMA Predictor 
ema_func <- function(lambda) {
  ema_tmp = EMA(Greturns, n = 1, ratio = lambda)
  rmse_tmp = rmse(Greturns[-length(Greturns)], ema_tmp[-1])
  return(rmse_tmp)
}
P_opt = optimize(ema_func, interval = c(-1,1))
P_opt
#Question 4 ---------------------------------

#Check if AR model satisfies and stationarity
#stationarity
roots = polyroot(c(1,-AR_4$coef[1:4]))
croots = 1/roots
Mod(croots)

#Check if ARMA model satisfies and stationarity and invertibility 
#stationarity
roots = polyroot(c(1,-ARMA_22$coef[1:2]))
croots = 1/roots #Characteristic Roots
Mod(croots) #Absolute value of the roots, if < 1 then stationary!

#Invertibility
roots = polyroot(c(1,ARMA_22$coef[3:4]))
roots = polyroot(c(1,0,-0.54))
mr = Mod(roots) #Absolute value of the roots, if > 1 then invertible!

#Question 5 ---------------------------------
#Forecasting
#AR(4)
mForecast = Arima(Greturns[1:(length(Greturns)-10)],order = c(4,0,0), 
                  fixed=c(0,0,0,NA,0))
P = predict(mForecast,10)
plot((length(Greturns)-9):length(Greturns),ylim = c(-0.2,0.2), xlab = "Time Step",
     ylab = "Log Returns", main = "AR(4) Compared With Actual Values"  )
points(1:10,P$pred, type = "b", col = "red")
points(1:10,Greturns[(length(Greturns)-9):length(Greturns)],
       type ="b", col = "blue")
lines(1:10,P$pred + 1.96*P$se, col = "orange")
lines(1:10,P$pred - 1.96*P$se, col = "orange")
legend(8,0.21, legend = c("Actual","Forecast","Prediction Interval"),
       col = c("blue","red","orange"), lty = 2, cex = 0.5)

#ARMA(2,2)
mForecast = Arima(Greturns[1:(length(Greturns)-10)],order = c(2,0,2), 
                  fixed=c(0,NA,0,NA,0))
P = predict(mForecast,10)
plot((length(Greturns)-9):length(Greturns),ylim = c(-0.2,0.2), 
     xlab = "Time Step", ylab = "Log Returns", 
     main = "ARMA(2,2) Compared With Actual Values" )
points(1:10,P$pred,type = "b", col = "red")
points(1:10,Greturns[(length(Greturns)-9):length(Greturns)],
       type ="b", col = "blue")
lines(1:10,P$pred + 1.96*P$se, col = "orange")
lines(1:10,P$pred - 1.96*P$se, col = "orange")
legend(8,0.21, legend = c("Actual","Forecast","Prediction Interval"),
       col = c("blue","red","orange"), lty = 2, cex = 0.5)

