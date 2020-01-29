library("fBasics")
library("TSA")
library("forecast")
library("tidyverse")
library("Metrics")
library("TTR")
library("fUnitRoots")
library("fGarch")
library("rugarch")
GLEN = read.csv("GLEN.L.csv",sep=",");
Gprice <- GLEN[,6]; #stock price
Greturns <- log(Gprice[-1] / Gprice[-length(Gprice)]); #mlog returns 
dt <- seq(as.Date("2013/06/17"), as.Date("2017/02/20"), "weeks");
dtr <- seq(as.Date("2013/06/24"), as.Date("2017/02/20"), "weeks");
GLENa = data.frame(Greturns, dtr) #dataframe for returns
GLENb = data.frame(Gprice,dt)  #datafram for price
# Question 1 ---------------------------------
#Exploratory Analysis

#Testing for stationarity 
t.test(Gprice)
t.test(Greturns)
acf(Greturns)
adfTest(Gprice, type = "c")
adfTest(Greturns, type = "nc")
#testing for whitenoise
Box.test(Gprice, lag = max(5,log(length(Gprice))), type= "Ljung-Box")
Box.test(Greturns, lag = max(5,log(length(Greturns))), type= "Ljung-Box")
acf(Greturns)
pacf(Greturns)
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
#Question 2 ------------------------------------------------
#Investigating Linear Dependence
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
#Order Specification
t = eacf(Greturns)
t
t$eacf
#Model Fittings
Arima(Greturns, order = c(2,0,2))
ARMA_22 = Arima(Greturns, order = c(2,0,2),
                fixed = c(0,NA,0,NA,0)) 
ARMA_22
#Model Validation
Box.test(ARMA_22=$residuals, lag = max(7,log(length(ARMA_22$residuals))), 
         fitdf = 2)
tsdiag(ARMA_22)
#Comparing AR(4) and ARMA(2,2)

#Question 3 ------------------------------------------------
#Fitting ARCH and GARCH
a = ARMA_22$residuals
acf(a)
pacf(a)
#Checking for conditional heteroscedasticity
acf(a^2)
pacf(a^2)
ar(a^2)$aic
Box.test(a^2,lag = max(7,log(length(a))),type = "Ljung")
#Fitting ARCH(1)
mArch_1 = garchFit(~garch(1,0),a,trace=F)
summary(mArch_1) #-2.565277 -2.514379 -2.565755 -2.544663 
#Fitting ARCH(2)
mArch_2 = garchFit(~garch(2,0),a,trace=F)
summary(mArch_2) #-2.745197 -2.677333 -2.746042 -2.717712 
#Fitting GARCH(1,1)
mGarch_11 = garchFit(~garch(1,1),a,trace=F) #Best Model
summary(mGarch_11) #-2.876149 -2.808284 -2.876993 -2.848663 
#Fitting GARCH(1,2)
mGarch_12 = garchFit(~garch(1,2),a,trace=F)
summary(mGarch_12) #-2.864690 -2.779860 -2.866001 -2.830333
#Fitting GARCH(2,1)
mGarch_21 = garchFit(~garch(2,1),a,trace=F)
summary(mGarch_21) #-2.907729 -2.822899 -2.909040 -2.873372 
#Fitting a joint ARMA(2,2)+GARCH(1,1) model.
Joint_22_11 = garchFit(formula = ~arma(2,2)+garch(1,1),
                       data = Greturns, cond.dist="norm",trace=F)
summary(Joint_22_11)  #IC: -2.856312 -2.720583 -2.859602 -2.801341 
#Fitting a joint ARMA(0,0)+GARCH(1,1) model.
Joint_00_11 = garchFit(formula = ~arma(0,0)+garch(1,1),
                       data = Greturns, cond.dist="norm",trace=F)
summary(Joint_00_11)  #IC: -2.860848 -2.792983 -2.861692 -2.833362 

#Attempting to fix omega to zero.
spec = ugarchspec(variance.model = list(model = "sGARCH",
                garchOrder = c(1,1)), mean.model = list(armaOrder = c(0,0)),
                  fixed.pars = list(omega = 0), distribution.model = "std")
M = ugarchfit(x,spec = spec)
M                  #not good
#Adjusting for distribution
MFinal =  garchFit(formula = ~arma(0,0)+garch(1,1),
                   data = Greturns, cond.dist="std",trace=F)
summary(MFinal)  #IC: -2.860848 -2.792983 -2.861692 -2.833362 
#Model Validation of ARMA(0,0)+GARCH(1,1)
res = residuals(MFinal)
acf(res)
pacf(res)
#Question 4 ------------------------------------------------
T = length (Greturns)
vol = MFinal@sigma.t #Extracting volatility
#Volatility and x_t on same graph 
plot(dt[-1], Greturns , type='l', xlab="Date", ylab = ' ', ylim = c(-0.25,0.29),
     main = 'Graph of Log Returns versus Fitted Volatility Over Time')
par(new=T)
plot(dt[-1],vol, type='l', col='blue', xlab="Date", ylab = ' ', ylim = c(-0.25,0.29))
legend("topright", legend = c("Log Returns","Fitted Volatility"),
       col = c("black","blue"), lty = 1, cex = 0.5)

#volatility against previous return
lagged1<- lag(log_ret,k=1)
plot(MFinal@sigma.t[2:T],MFinal@residuals[-T],xlab="Fitted Volatility",
     ylab="Previous Return", col = "red")

w#EGARCH
spec = ugarchspec(variance.model = list(model = "eGARCH",garchOrder = c(1,1)),
                  mean.model = list(armaOrder = c(0,0)),
                   distribution.model = "std")
Mg = ugarchfit(Greturns,spec = spec)
Mg                  #AIC: -2.9184 #BIC: -2.8166

#GARCH-M
spec = ugarchspec(variance.model = list(model = "sGARCH",garchOrder = c(1,1)),
                  mean.model = list(armaOrder = c(0,0),archm = TRUE),
                  distribution.model = "std");
Mm = ugarchfit(Greturns,spec = spec);
Mm                  #AIC: -2.9184 #BIC: -2.8166

