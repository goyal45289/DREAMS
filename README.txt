DREAMS — Disaster Response and Emergency Assistance Management System (corrected)
============================================

This version includes the Firebase Realtime Database JavaScript SDK.
The app subscribes to /aidris/sharedState and applies remote updates to the
dashboard. Incident creation, mission completion, pending retry and reset
actions write the shared state to Firebase.

DEPLOY THE CORRECTED VERSION
1. Extract this ZIP into a NEW folder so you can keep the old copy as backup.
2. Open the extracted DREAMS_Command_Center folder in VS Code.
3. Open Terminal in that folder and run:
     firebase deploy --only hosting
4. Wait for "Deploy complete!".
5. Refresh the same website URL on both laptop and phone.

IMPORTANT
- Database rules are currently public read/write as requested. Anyone with the
  database endpoint can read, change or delete data. Use demo data only.
- This first shared version synchronizes a whole state snapshot. If two members
  write at exactly the same time, one update can overwrite another. We should
  upgrade to per-incident transactions and enable authentication before using
  this for real response operations.
- Start the random surprise simulation on only one device at a time.
- Firebase Hosting serves the web app. The C++ files are included for reference;
  Hosting does not run the C++ backend.


ARRAY FORMAT COMPATIBILITY FIX
This version converts Firebase numeric-key objects (for example incidents/0)
into JavaScript arrays before rendering. This fixes the case where the database
contains incidents but the browser board incorrectly displays "No incidents".


PERMANENT FLEET SERIALIZATION FIX
The fleet array no longer receives an innerHTML property during rendering. The
Firebase snapshot writes only explicit resource fields, and the reader ignores
non-numeric object keys left over from older data. This prevents the old
innerHTML field from returning and prevents it being counted as a fourth unit.
