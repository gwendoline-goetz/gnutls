/*
 * Copyright (C) 2010-2012 Free Software Foundation, Inc.
 *
 * Author: Nikos Mavrogiannopoulos
 *
 * This file is part of GnuTLS.
 *
 * GnuTLS is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GnuTLS is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <config.h>

#include <gnutls/gnutls.h>
#include <gnutls/x509.h>
#include <gnutls/openpgp.h>
#include <gnutls/pkcs12.h>
#include <gnutls/pkcs11.h>
#include <gnutls/abstract.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>

/* Gnulib portability files. */
#include <read-file.h>
#include <progname.h>
#include <version-etc.h>

#include "p11tool-args.h"
#include "p11tool.h"
#include "certtool-common.h"

static void cmd_parser (int argc, char **argv);

static FILE *outfile;
int batch = 0;

static void
tls_log_func (int level, const char *str)
{
  fprintf (stderr, "|<%d>| %s", level, str);
}


int
main (int argc, char **argv)
{
  set_program_name (argv[0]);
  cmd_parser (argc, argv);

  return 0;
}

static void
cmd_parser (int argc, char **argv)
{
  int ret, debug = 0;
  common_info_st cinfo;
  unsigned int action = 1, pkcs11_type = -1, key_type = GNUTLS_PK_UNKNOWN;
  const char* url = NULL;
  unsigned int detailed_url = 0;
  unsigned int login = 0, bits = 0;
  const char* label = NULL, *sec_param = NULL;
  
  optionProcess( &p11toolOptions, argc, argv);
  
  if (ENABLED_OPT(DEBUG))
    debug = OPT_VALUE_DEBUG;

  gnutls_global_set_log_function (tls_log_func);
  gnutls_global_set_log_level (debug);
  if (debug > 1)
    printf ("Setting log level to %d\n", debug);

  if ((ret = gnutls_global_init ()) < 0)
    error (EXIT_FAILURE, 0, "global_init: %s", gnutls_strerror (ret));

  if (ENABLED_OPT(PROVIDER))
    {
      ret = gnutls_pkcs11_init (GNUTLS_PKCS11_FLAG_MANUAL, NULL);
      if (ret < 0)
        fprintf (stderr, "pkcs11_init: %s", gnutls_strerror (ret));
      else
        {
          ret = gnutls_pkcs11_add_provider (OPT_ARG(PROVIDER), NULL);
          if (ret < 0)
            error (EXIT_FAILURE, 0, "pkcs11_add_provider: %s",
                   gnutls_strerror (ret));
        }
    }
  else
    {
      ret = gnutls_pkcs11_init (GNUTLS_PKCS11_FLAG_AUTO, NULL);
      if (ret < 0)
        fprintf (stderr, "pkcs11_init: %s", gnutls_strerror (ret));
    }

  if (ENABLED_OPT(OUTFILE))
    {
      outfile = safe_open_rw (OPT_ARG(OUTFILE), 0);
      if (outfile == NULL)
        error (EXIT_FAILURE, errno, "%s", OPT_ARG(OUTFILE));
    }
  else
    outfile = stdout;

  memset (&cinfo, 0, sizeof (cinfo));
  
  if (ENABLED_OPT(SECRET_KEY))
    cinfo.secret_key = OPT_ARG(SECRET_KEY);

  if (ENABLED_OPT(LOAD_PRIVKEY))
    cinfo.privkey = OPT_ARG(LOAD_PRIVKEY);

  if (ENABLED_OPT(PKCS8))
    cinfo.pkcs8 = 1;

  if (ENABLED_OPT(INDER) || ENABLED_OPT(INRAW))
    cinfo.incert_format = GNUTLS_X509_FMT_DER;

  if (ENABLED_OPT(LOAD_CERTIFICATE))
    cinfo.cert = OPT_ARG(LOAD_CERTIFICATE);

  if (ENABLED_OPT(LOAD_PUBKEY))
    cinfo.pubkey = OPT_ARG(LOAD_PUBKEY);
    
  if (ENABLED_OPT(LIST_TOKENS))
    action = ACTION_PKCS11_TOKENS;
  else if (ENABLED_OPT(LIST_MECHANISMS))
    action = ACTION_PKCS11_MECHANISMS;
  else if (ENABLED_OPT(LIST_ALL))
    {
      pkcs11_type = PKCS11_TYPE_ALL;
      action = ACTION_PKCS11_LIST;
    }
  else if (ENABLED_OPT(LIST_ALL_CERTS))
    {
      pkcs11_type = PKCS11_TYPE_CRT_ALL;
      action = ACTION_PKCS11_LIST;
    }
  else if (ENABLED_OPT(LIST_CERTS))
    {
      pkcs11_type = PKCS11_TYPE_PK;
      action = ACTION_PKCS11_LIST;
    }
  else if (ENABLED_OPT(LIST_ALL_PRIVKEYS))
    {
      pkcs11_type = PKCS11_TYPE_PRIVKEY;
      action = ACTION_PKCS11_LIST;
    }
  else if (ENABLED_OPT(LIST_ALL_TRUSTED))
    {
      pkcs11_type = PKCS11_TYPE_TRUSTED;
      action = ACTION_PKCS11_LIST;
    }
  else if (ENABLED_OPT(EXPORT))
    {
      action = ACTION_PKCS11_EXPORT_URL;
    }
  else if (ENABLED_OPT(WRITE))
    action = ACTION_PKCS11_WRITE_URL;
  else if (ENABLED_OPT(INITIALIZE))
    action = ACTION_PKCS11_TOKEN_INIT;
  else if (ENABLED_OPT(DELETE))
    action = ACTION_PKCS11_DELETE_URL;
  else if (ENABLED_OPT(GENERATE_ECC))
    {
      key_type = GNUTLS_PK_EC;
      action = ACTION_PKCS11_GENERATE;
    }
  else if (ENABLED_OPT(GENERATE_RSA))
    {
      key_type = GNUTLS_PK_RSA;
      action = ACTION_PKCS11_GENERATE;
    }
  else if (ENABLED_OPT(GENERATE_DSA))
    {
      key_type = GNUTLS_PK_DSA;
      action = ACTION_PKCS11_GENERATE;
    }
  else 
    {
      USAGE(1);
    }
    
  if (ENABLED_OPT(DETAILED_URL))
    detailed_url = 1;

  if (ENABLED_OPT(LOGIN))
    login = 1;

  if (ENABLED_OPT(URL))
    {
      url = OPT_ARG(URL);
    }

  if (ENABLED_OPT(LABEL))
    {
      label = OPT_ARG(LABEL);
    }

  if (ENABLED_OPT(BITS))
    {
      bits = OPT_VALUE_BITS;
    }

  if (ENABLED_OPT(SEC_PARAM))
    {
      sec_param = OPT_ARG(SEC_PARAM);
    }

  if (debug > 0)
    {
      fprintf(stderr, "Private: %s\n", ENABLED_OPT(PRIVATE)?"yes":"no");
      fprintf(stderr, "Trusted: %s\n", ENABLED_OPT(TRUSTED)?"yes":"no");
      fprintf(stderr, "Login: %s\n", ENABLED_OPT(LOGIN)?"yes":"no");
      fprintf(stderr, "Detailed URLs: %s\n", ENABLED_OPT(DETAILED_URL)?"yes":"no");
      fprintf(stderr, "\n");
    }

  switch (action)
    {
    case ACTION_PKCS11_LIST:
      pkcs11_list (outfile, url, pkcs11_type,
                   login, detailed_url, &cinfo);
      break;
    case ACTION_PKCS11_TOKENS:
      pkcs11_token_list (outfile, detailed_url, &cinfo);
      break;
    case ACTION_PKCS11_MECHANISMS:
      pkcs11_mechanism_list (outfile, url, login,
                             &cinfo);
      break;
    case ACTION_PKCS11_EXPORT_URL:
      pkcs11_export (outfile, url, login, &cinfo);
      break;
    case ACTION_PKCS11_WRITE_URL:
      pkcs11_write (outfile, url, label,
                    ENABLED_OPT(TRUSTED), ENABLED_OPT(PRIVATE), login, &cinfo);
      break;
    case ACTION_PKCS11_TOKEN_INIT:
      pkcs11_init (outfile, url, label, &cinfo);
      break;
    case ACTION_PKCS11_DELETE_URL:
      pkcs11_delete (outfile, url, 0, login, &cinfo);
      break;
    case ACTION_PKCS11_GENERATE:
      pkcs11_generate (outfile, url, key_type, get_bits(key_type, bits, sec_param), 
                       label, ENABLED_OPT(PRIVATE), detailed_url, login, 
                       &cinfo);
      break;
    }
  fclose (outfile);

#ifdef ENABLE_PKCS11
  gnutls_pkcs11_deinit ();
#endif
  gnutls_global_deinit ();
}
