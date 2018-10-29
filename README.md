# Machine learning project 1 : the Higgs Boson challenge
As intermediate project of the Machine Learning course at EPFL, we were asked to face a classification problem in the context of high-energy physics.  

This document outlines the necessary steps to build the model that gives the best reached prediction. After detailing the data cleaning procedure, different models were compared (which can be found on the report). Given this evidence, the ridge regression was chosen and improved by a further feature augmentation. Thus, an accuracy of around 0.832 (On Kaggle and by cross-validation) was reached.

##### Table of Contents  
* [Getting started](#start)
* [Running the prediction](#running)
* [Description of the ML system](#description)
* [Structure of the files](#structure)
* [Authors](#authors)

<a name="start" />

## Getting started
### Prerequisites
You need a recent python installation (`> 3.5`) and the latest version of numpy (`1.14.0` as of oct 2018). The project has been runned and tested with an Anaconda installation.

Data set train.csv and test.csv must also be present to be able to make the predictions. You can find them on the [Kaggle](https://www.kaggle.com/c/epfml18-higgs) page.

<a name="running" />

## Running the prediction

To run and predict from the two data set that are given, you need to run the file `run.py` with all the base files (`implementations.py`, `load_save.py`, `methods.py`, `manipulate_data.py`, `clean_data.py`) present in the subfolder `base/`. The exact python version used for the final prediction on Kaggle is `3.6.4` and `1.14.0` for numpy. With other versions, results could be different or it could not work.

<a name="description" />

## Description of the Machine learning system
The detail of the execution of the run.py, which corresponds to the best model that our team could make, is described here.
### Data preparation
At the beginning of the file, there is a variable named `path_csv` which is empty by default. If you want to load the `train.csv` and `test.csv` in another folder than the folder in which `run.py` is you should change this variable. The data is loaded in the beginning of the file.

All the data preprocessing is done in the functions `data_preprocessing_tr` and `data_preprocessing_te` which preprocesses respectively the data of the train set and the test set. 

#### `data_preprocessing_tr(subset=250000, seed=1, sigma=10)`
This function does the following steps (on the training set) :
* Randomly shuffles the data of the training set and select a subset if `subset` has been defined (the whole train set has 250000 rows)
* Select the categorical variables column (#22, PRI Jet Number) out of the input matrix
* Standardizes the data by replacing the undefined values of -999 by the mean of the other defined values (on a whole column), and ignores the standardization on the categorical column (#22).
* Select the indices of the rows of outliers present in the data (with a given `sigma`)

And returns the new training input matrix `x_tr`, the output vector `yb_tr`, the categorical variables column `categorical_variables_tr` and the indices of the outliers `outliers_ind`

#### `data_preprocessing_te()`
This function does the following steps (on the test set) :
* Select the categorical variables column (#22, PRI Jet Number) out of the input matrix
* Standardizes the data by replacing the undefined values of -999 by the mean of the other defined values (on a whole column), and ignores the standardization on the categorical column (#22).

### Feature engineering
#### `feature_engineering(x_tr, cat_var_tr, p_degree, feat_exp_degree)`
There are three steps done in the feature enineering :
 * Building the powers of each column until `p_degree`
 * Replacing the ones column by the categorical variable divided into four different columns (dummy variable method, explained in more details in the report)
 * Builds the column-wise multiplication for each column `a` and `b` of the input matrix (`a*b`) and if `feat_exp_degree > 1` builds also the feature expansion for each column `a` and `b` : `(a+b)^2`, `(a+b)^3`, ..., `(a+b)^feat_exp_degree`
 
Returns the new traing input_matrix `x_tr` with the added features

### Cross-validation step
#### `train_model(sigma, seed, degree, feat_exp_degree, lambdas, k_fold, subset=250000):`
Once the data has been preprocessed, and the features expanded, it is possible to begin cross-validation. With a given `k_fold` and given `lambdas` (and the other arguments necessary for the feature engineering), the `train_model` runs through all the `lambdas` trying to find the best `lambda_` value that gives the best test accuracy.

Returns the weights that gives the best accuracy.

### Generation of the prediction
#### `predict(weights, degree, feat_exp_degree, threshold):`
With given `weights` vector, tries to predict from the test set. It makes all the steps of data preprocessing (except outlier removal) and feature engineering that have been made in `train_model` but with the test set. Then uses the function `predict_labels` with the given `threshold` to make the actual prediction.

Returns the output vector `y_pred`

These few lines of code at the end of the file are sufficient to generate a prediction. The parameters can be changed to fine tune the model :
```
#Parameters of the model that has been selected to give the best results
sigma = 12
seed = 2
degree = 12
feat_exp_degree = 3
k_fold = 4
threshold = 0.03

lambdas = [4.08e-05] #np.logspace(-4.5, -3.5, 10) #The best lambda found in our current model is 4.0842386526745174e-05
weights = train_model(sigma, seed, degree, feat_exp_degree, lambdas, k_fold)
y_pred = predict(weights, degree, feat_exp_degree, threshold)

create_csv_submission(ids_te, y_pred, path_csv + "predictions.csv")
```

<a name="structure" />

## Structure of the files

What follows is a basic description of what can be found in the base code of the project. For the sake of having a readable README file, the complete description (descriptions, arguments, returns, notes) of the functions has not been included. The more complete documentation (documented with python docstrings) can be found directly in the code.

### base/implementations.py
`implementations.py` contains all the methods for finding the best weight vector with a given train set. The following methods have been implemented (which are asked in the project guidelines) :
* **Least squares** using normal equations
* **Least squares** using gradient descent
* **Least squares** using stochastic gradient descent
* **Ridge regression** with a regularization factor lambda
* **Logistic regression** using gradient descent
* **Regularized regression** using gradient descent with a regularization factor lambda

### base/load_save.py
`load_save.py` contains all functions relative to load the data (test.csv and train.csv) and save the prediction in a csv. The following functions are implemented :
* **load_csv_data** : loads the csv of a test or train csv and returns the corresponding labels `y`, input matrix `tx` and event ids `ids`
* **create_csv_submission** : creates the final csv with the given `ids` and predictions `y_pred` in the file `name`

### base/methods.py
`methods.py` contains all the functions relative to the cross-validation. The following functions are implemented :
* **build_k_indices** : builds and returns k indices (randomly shuffled) in k_fold different arrays of a vector of length num_rows. Use by the cross_validation function
* **cross_validation** : applies cross-validation on a given data set with a certain number of k-fold and can also delete the given outlier in the train sets but not the test set (because outliers should also be predicted in the final test set).

### base/manipulate_data.py
`manipulate_data.py` contains all the functions relative to the manipulation of the data (e.g feature expansion, polynomial build, ...). The following functions are implemented :
* **split_data** : Splits (and shuffles) the data of the output vector `y` and input matrix `tx` into two set : training set and test set
* **expand_features** : builds for each column a,b of the input matrix `tx` (with shape (N,D) ) the following polynomial : (a + b)^degree and returns the original matrix `tx` along with the new features columns. If `degree` is set to 1, then it makes for each column a,b of the input matrix tx a column-wise multiplication : a\*b.
* **build_poly** : builds for each column a of the input matrix `tx` the following powers : a, a^2, ..., a^degree and returns the original matrix `tx` along with the new features.
* **svd_features_reduction** : allows to detect the principal directions of the data matrix and so, it permits to avoid troubles related to ill conditionement due to features dependance.
* **predict_labels** : generates class predictions given `weights`, and a test `data` matrix with the following rule : if x <= threshold then y = -1 otherwise y = 1. `Threshold` is set to 0 by default.
* **accuracy** : gives the accuracy (percentage of correct answers) for a given data set (`x_te`, `y_te`) with the `weights`. Uses the function `predict_labels` to predict the labels. If x <= threshold then y = -1 otherwise y = 1. `Threshold` is set to 0 by default.
* **find_best_threshold** : finds the best threshold for a given set data set (`y_te`, `x_te`) that gives the best accuracy.

### base/clean_data.py
`clean_data.py` contains all the functions relative to the cleaning of the data (outlier removal and standardization). The following functions are implemented :
* **remove_outliers** : removes the outliers (if one outlier is in a row, the whole row is removed) from a given indices array.
* **outliers_indices** : returns the indexes of rows where value > sigma
* **standardize** : Standardize the data set `x` and also checks for undefined values which then will be set to the mean of the rest of defined values (i.e. set to 0). Every column present in `exclude_columns` will be ignored by the standardization. Every column present in `delete_columns` will be deleted.

<a name="authors" />

## Authors
Team JLJ on Kaggle
* **Joachim Koerfer**, currently in Master of Computational Science and Engineering, EPFL
* **Luca Viano**, currently in Master of Computational Science and Engineering, EPFL
* **Jannik Reichert**, currently in Bachelor in Computer Science, Technische Universität Berlin
