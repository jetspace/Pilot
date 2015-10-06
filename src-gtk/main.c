#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <time.h>

#define EXEC "python2 src/main.py -t "
#define VOICE "python2 src/main.py -v"

GtkWidget *resultbox;
GtkWidget *v;
GtkWidget *mainbox;

static gboolean quit(GtkWidget *w, GdkEvent *e, gpointer p)
{
  gtk_main_quit();
  return FALSE;
}
gboolean voice = FALSE;
static gboolean trigger(GtkWidget *w, GdkEvent *e, GtkEntry *ent);
static gboolean trigger_voice(GtkWidget *w, GdkEvent *e, GtkEntry *ent)
{
  voice = TRUE;
  GtkWidget *icon = gtk_button_get_image(GTK_BUTTON(v));
  gtk_image_set_from_icon_name(GTK_IMAGE(icon), "media-record", GTK_ICON_SIZE_BUTTON);
  gtk_widget_queue_draw (icon);
  while (gtk_events_pending ())
    gtk_main_iteration ();
  trigger(w, e, ent);
  gtk_image_set_from_icon_name(GTK_IMAGE(icon), "audio-input-microphone", GTK_ICON_SIZE_BUTTON);
  gtk_widget_queue_draw(icon);
  while (gtk_events_pending ())
    gtk_main_iteration ();
  return FALSE;
}

static gboolean trigger(GtkWidget *w, GdkEvent *e, GtkEntry *ent)
{
  gtk_widget_destroy(resultbox);
  resultbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_pack_end(GTK_BOX(mainbox), resultbox, TRUE, TRUE, 0);

  char *cmd = g_strdup_printf("%s'%s'", EXEC, gtk_entry_get_text(ent));
  char buffer[2048];
  FILE *pilot;
  if(!voice)
    pilot = popen(cmd, "r");
  else pilot = popen(VOICE, "r");

  GtkWidget *frame;
  GtkWidget *new_result;

  while(fgets(buffer, 2048, pilot) != NULL)
  {

    if(strncmp(buffer, "PILOT:", 6) == 0)
    {
        if(strncmp(buffer, "PILOT:END", 9) != 0)
        {
          frame = gtk_frame_new(NULL);
          new_result = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        }
        else
        {
          gtk_container_add(GTK_CONTAINER(frame), new_result);
          //add new element
          gtk_box_pack_start(GTK_BOX(resultbox), frame, FALSE, FALSE, 0);
          gtk_widget_show_all(resultbox);
        }
    }
    else if(strncmp(buffer, "LABEL:", 6) == 0)
    {
        strtok(buffer, ":");
        char *text = strtok(NULL, "\n");
        GtkWidget *temp = gtk_label_new("");
        gtk_label_set_markup(GTK_LABEL(temp), text);
        gtk_box_pack_start(GTK_BOX(new_result), temp, FALSE, FALSE, 0);
    }
  }


  pclose(pilot);
  g_free(cmd);
  voice = FALSE;
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
  v = gtk_button_new_from_icon_name("audio-input-microphone", GTK_ICON_SIZE_BUTTON);

  gtk_box_pack_start(GTK_BOX(box), v, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), inp, TRUE, TRUE, 0);
  gtk_box_pack_end(GTK_BOX(box), button, FALSE, FALSE,0);


  mainbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_pack_start(GTK_BOX(mainbox), box, FALSE, FALSE, 0);



  gtk_container_add(GTK_CONTAINER(win), mainbox);

  gtk_widget_show_all(win);

  //SIGNALS
  g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(quit), NULL);
  g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(trigger), inp);
  g_signal_connect(G_OBJECT(v), "clicked", G_CALLBACK(trigger_voice), inp);


  gtk_main();
  return 0;
}
