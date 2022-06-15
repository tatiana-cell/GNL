#include <stdlib.h>
#define BUFFER_SIZE 1000
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>



size_t ft_strlen(const char *s)
{
    size_t  i;
    i = 0;
    while (s && s[i])
        i++;
    return (i);
}


char*ft_strjoin(char const *s1, char const *s2)
{
    char    *str;
    int j;
    size_t  len; 

    if (s1)
        len = ft_strlen(s1);
    if (s2)
        len = ft_strlen(s1) + ft_strlen(s2);
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    len = 0;
    while (s1 && s1[len])
    {
        str[len] = s1[len];
        len++;
    }
    j = -1;
    while (s2 && s2[++j])
        str[len++] = s2[j];
    str[len] = '\0';
    return (str);

}

char*ft_strchr(char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char*)s);
        s++;    
    }
    if (!*s && !c)
        return ((char*)s);
    return (NULL);
}

char    *ft_select(char *buf, int *ret)
{
    int i;
    char    *dest;

    i = 0;
    while (buf && buf[i] && buff[i] != '\n')
        i++;
    dest = malloc(i + 1);
    if (!dest)
        return (NULL);
    if (ft_strchr(buf, '\n') != 0)  
        *ret = 1;
    i = 0;
    while (buf && buf[i] && buf[i] != '\n')      
    {
        dest[i] = buf[i];
        i++;
    }
    dest[i] ='\0';
    return (dest);
 }


 char   *ft_select2(char *buf)
 {
     int    i;
     int    j;
     char   *dest;

     i = 0;
     while (buf && buf[i] && buff[i] != '\n')
        i++;
    dest = malloc(sizeof(*dest) * (ft_strlen(buf) - i + 1));
    if (!dest)
        return (NULL);
    j = 0;
    while (buf && buf[i])
        dest[j++] = buf[++i];
    dest[j] = '\0';
    return (dest);

 }

int get_next_line(int fd, char **line)
{
    char    buf[BUFFER_SIZE + 1];
    int ret;
    static char *str = NULL;
    char    *temp;

    ret = BUFFER_SIZE;
    if (fd < 0 || fd > 1023 || !line || BUFFER_SIZE <= 0)
        return (-1);
    while (ret > 0)    
    {
        ret = read(fd, buf, BUFFER_SIZE);
        if (ret == -1)
            return (-1);
        buf[ret] = 0;  //la fin du fichier
        temp = str;
        str = strjoin(temp, buf);
        free(temp);
        if (ft_strchr(str, '\n'))
            break;

    }
    *line = ft_select(str, &ret); // on recupere ce qui a gauche de '\n'
    temp = str;
    str = ft_select2(temp); // on recup ce qui est a droite de '\n'
    free(temp);
    if (ret == 0 && (*str)[0] == 0)
    {
        free (*str);
        *str = NULL;

    }

    return (ret);
}

int main()
{
    int fd = open("coucou", O_RDONLY);
    char *line = NULL;
    int ret = get_next_line(fd, &line);

    while (ret != 0)
    {
        printf("\n\nTour de boucle\n\n");
        printf("%s", line);
        ret = get_next_line(fd, &line);
    }
}