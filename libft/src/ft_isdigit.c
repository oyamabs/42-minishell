/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchampio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:57:00 by tchampio          #+#    #+#             */
/*   Updated: 2024/10/14 14:52:41 by tchampio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <limits.h>

// Prototype de la fonction ft_isdigit que tu devras implémenter
int ft_isdigit(int c);

// Macros pour les couleurs
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BOLDWHITE   "\033[1m\033[37m"

// Fonction de test
void test_ft_isdigit(int c, int expected, int *success_count) {
    int result = ft_isdigit(c);

    if (result == expected) {
        printf(GREEN "Test passed: ft_isdigit(%d) == %d\n" RESET, c, result);
        (*success_count)++;
    } else {
        printf(RED "Test failed: ft_isdigit(%d) == %d (expected %d)\n" RESET,
	c, result, expected);
    }
}

int main() {
    int success_count = 0;
    int total_tests = 0;

    // Tests des chiffres (0-9)
    for (int i = '0'; i <= '9'; i++) {
        test_ft_isdigit(i, 1, &success_count);
        total_tests++;
    }

    // Tests des lettres (min et majuscule)
    for (int i = 'a'; i <= 'z'; i++) {
        test_ft_isdigit(i, 0, &success_count);
        total_tests++;
    }
    for (int i = 'A'; i <= 'Z'; i++) {
        test_ft_isdigit(i, 0, &success_count);
        total_tests++;
    }

    // Tests des caractères non imprimables
    for (int i = 0; i <= 31; i++) {
        test_ft_isdigit(i, 0, &success_count);
        total_tests++;
    }

    // Tests des symboles et autres caractères
    test_ft_isdigit('!', 0, &success_count); total_tests++;
    test_ft_isdigit('@', 0, &success_count); total_tests++;
    test_ft_isdigit('[', 0, &success_count); total_tests++;
    test_ft_isdigit('`', 0, &success_count); total_tests++;
    test_ft_isdigit('~', 0, &success_count); total_tests++;

    // Cas extrêmes avec limites des entiers
    test_ft_isdigit(INT_MAX, 0, &success_count); total_tests++;
    test_ft_isdigit(INT_MIN, 0, &success_count); total_tests++;

    // Résumé des résultats
    printf(BOLDWHITE "\nTotal tests: %d, Success: %d, Failures: %d\n" RESET,
    total_tests, success_count, total_tests - success_count);

    return 0;
}
*/
