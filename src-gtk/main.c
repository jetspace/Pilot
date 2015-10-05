#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>

#define EXEC "python2 src/main.py -t "

GtkWidget *resultbox;
GtkWidget *mainbox;

static gboolean quit(GtkWidget *w, GdkEvent *e, gpointer p)
{
  gtk_main_quit();
  return FALSE;
}

static gboolean trigger(GtkWidget *w, GdkEvent *e, GtkEntry *ent)
{
  gtk_widget_destroy(resultbox);
  resultbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_pack_end(GTK_BOX(mainbox), resultbox, TRUE, TRUE, 0);

  char *cmd = g_strdup_printf("%s'%s'", EXEC, gtk_entry_get_text(ent));
  char buffer[2048];
  FILE *pilot = popen(cmd, "r");

  while(fgets(buffer, 2048, pilot) != NULL)
  {
    if(strcmp(buffer, "PILOT:TIMECONVERT\n") == 0)
    {
        fgets(buffer, 2048, pilot);
        long t = atol(strtok(buffer, ","));
        char *z = g_strdup(strtok(NULL, ","));
        char *n = g_strdup(strtok(NULL, ","));
        char *zp = g_strdup(strtok(NULL, "\n"));

        GtkWidget *frame = gtk_frame_new(NULL);
        GtkWidget *new_result = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

        char *labeltext = g_strdup_printf("<big><b>Current time in %s:</b></big>", n);
        GtkWidget *label = gtk_label_new(labeltext);
        gtk_label_set_markup(GTK_LABEL(label), labeltext);

        g_free(labeltext);

        char *text = malloc(200);
        //%Y-%m-%d
        strftime(text, 200, "<b>%H:%M</b>", localtime ( &t ));

        GtkWidget *ti = gtk_label_new(text);
        gtk_label_set_markup(GTK_LABEL(ti), text);

        char *b = g_strdup_printf("<small>%s (%s)</small>", zp, z);
        GtkWidget *tz = gtk_label_new(zp);
        gtk_label_set_markup(GTK_LABEL(tz), b);
        g_free(b);

        gtk_box_pack_start(GTK_BOX(new_result), label, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(new_result), ti, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(new_result), tz, FALSE, FALSE, 0);

        gtk_container_add(GTK_CONTAINER(frame), new_result);

        //add new element
        gtk_box_pack_start(GTK_BOX(resultbox), frame, FALSE, FALSE, 0);
        gtk_widget_show_all(resultbox);

    }
    if(strcmp(buffer, "PILOT:WEATHER\n") == 0)
    {
        fgets(buffer, 2048, pilot);
        long d = atol(strtok(buffer, ","));
        char *c = g_strdup(strtok(NULL, ","));
        char *city = g_strdup(strtok(NULL, "\n"));

        GtkWidget *frame = gtk_frame_new(NULL);
        GtkWidget *new_result = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

        char *labeltext = g_strdup_printf("<big><b>Weather for %s:</b></big>", city);
        GtkWidget *label = gtk_label_new(labeltext);
        gtk_label_set_markup(GTK_LABEL(label), labeltext);
        g_free(labeltext);

        GtkWidget *ti = gtk_label_new(c);

        char *b = g_strdup_printf("<big>%ld °C</big>", d);
        GtkWidget *temp = gtk_label_new(b);
        gtk_label_set_markup(GTK_LABEL(temp), b);
        g_free(b);

        gtk_box_pack_start(GTK_BOX(new_result), label, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(new_result), ti, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(new_result), temp, FALSE, FALSE, 0);

        gtk_container_add(GTK_CONTAINER(frame), new_result);

        //add new element
        gtk_box_pack_start(GTK_BOX(resultbox), frame, FALSE, FALSE, 0);
        gtk_widget_show_all(resultbox);

    }
  }


  pclose(pilot);
  g_free(cmd);
  return FALSE;
}

int main(int argc, char **argv)
{
  gtk_init(&argc, &argv);

  GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_container_set_border_width(GTK_CONTAINER(win), 10);
  gtk_window_set_title(GTK_WINDOW(win), "JetSpace Pilot");

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);

  GtkWidget *inp = gtk_entry_new();
  GtkWidget *button = gtk_button_new_with_label(">");

  gtk_box_pack_start(GTK_BOX(box), inp, TRUE, TRUE, 0);
  gtk_box_pack_end(GTK_BOX(box), button, FALSE, FALSE,0);


  mainbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_pack_start(GTK_BOX(mainbox), box, FALSE, FALSE, 0);



  gtk_container_add(GTK_CONTAINER(win), mainbox);

  gtk_widget_show_all(win);

  //SIGNALS
  g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(quit), NULL);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(trigger), inp);


  gtk_main();
  return 0;
}
