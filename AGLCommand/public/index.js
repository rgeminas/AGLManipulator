var mainApp = angular.module('mainApp', []);


mainApp.controller("mainController", function mainController($http, $scope) {
    $scope.positions = [{value: 0}, 
                        {value: 0},
                        {value: 0},
                        {value: 0},
                        {value: 0},
                        {value: 0}];

    $scope.submit = function () {
        $http.post('./positions', { positions: $scope.positions })
            .success(function(msg) {
                alert('success!');
            });
    }
});
