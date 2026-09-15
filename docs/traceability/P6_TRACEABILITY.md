# CardMind Phase 6 traceability

This is the only active Phase 6 matrix. `ROADMAP.md` defines product scope; this file records the
minimum atomic plan and only observed evidence. Phase 6 closes the remaining user-facing Web and
Device gaps through a stable, measured Wi-Fi baseline without introducing USB production work.

## Phase lock

- Phase source is authenticated remote `develop` at
  `fd9373aa93bd04e217b2e58c6a6ee75b80e3eaf8`, the reviewed merge of Phase 5 through PR #3.
  Remote `main` remains `681cc8ffa9b6d26897d4847001d5d57f17b5d340`.
- Work branch is `feature/phase-6-ui-stable-baseline`, created locally from that exact `develop`
  commit after the user-requested system reboot.
- The retained Phase 3 stash and the three approved Architect-owned untracked `.codex/agents`
  definitions are outside Phase 6 ownership and must remain untouched.
- Phase 3 owns policy, confirmation, audit, cancellation, projects, chats, files and the original
  Web/Device interaction boundaries. Phase 4 owns SSH profiles, the single terminal and controlled
  remote actions. Phase 5 owns the approved one-shot Python cycle and same-address handoff. Phase 6
  may extend only the explicit UI, profile, session, presence, reconnect and stable-baseline seams.
- The general-mode free-heap floor remains 70 KiB. Phase 4's missing numeric active-SSH resource
  sample and Phase 5's explicitly retained one-shot residuals are inherited facts, not Phase 6
  regressions or authority to broaden scope.

## Locked product contract

- Reconcile every non-deferred user-facing capability completed through Phase 5 across its required
  Device and Web surfaces. Preserve the established concepts, names, permissions and state.
- Complete responsive Web parity for desktop, tablet and phone without forcing identical layouts.
  Complete Cardputer navigation within the measured 240x135 display and existing input model.
- Add a bounded API-profile and model-preset set sized by measured NVS capacity; do not create a
  paginated profile framework.
- Offer authentication lifetimes of 15 minutes, 1 hour, 8 hours and until reboot. Authentication
  lifetime is independent from browser presence.
- Each visible Web tab sends a bounded heartbeat. While the existing synchronous WebServer is
  available to process requests, presence becomes waiting within 30 seconds after the last accepted
  heartbeat while authentication remains valid. A blocking foreground request makes presence
  temporarily unobservable and must show the existing operation state or compact Busy, never a
  connected claim. Handler return evaluates the original heartbeat timestamp without renewal or
  grace; only a newly accepted visible-tab heartbeat restores connected.
- One closing tab cannot hide another live tab because any remaining visible tab continues the
  aggregate heartbeat. `pagehide`/`sendBeacon` hints are optional and must not clear aggregate
  presence. Existing transfers are neither redesigned nor restricted for this indicator.
- Reuse the existing reconnect path while preserving the active project, active view and drafts.
  Exact scroll restoration is outside scope unless a measured defect changes `ROADMAP.md` first.
- Reuse existing diagnostics, export, clipboard, file/download and single-QR paths. Add only explicit
  missing-SD, provider-outage and unavailable-optional-API states required by the roadmap.
- Close with one exact, recoverable Wi-Fi baseline containing source, binary hash, build options,
  flash/RAM/heap/largest-block/stack, user-visible latency and exact-owned cleanup evidence.

## Explicit non-goals

- No USB/NCM production code, abstraction, experiment or preparation; no local HTTPS or installable
  PWA metadata before a trusted-origin delivery path exists.
- No new design-system dependency, front-end framework, route family, storage framework, second Web
  server, second dashboard, share center, temporary-link service or multi-frame QR.
- No encrypted secret export before the Phase 9 physical-access and recovery decision.
- No background job, queue, resume, generalized retry, tool-handle or recovery framework.
- No reopening of completed P3/P4/P5 ownership without Architect authorization and a canonical
  matrix update.

Status values are `pending`, `in_progress`, and `completed`.

## Execution matrix

| ID | Atomic boundary | Required observation | Status |
| --- | --- | --- | --- |
| P6-01 | Canonical phase transition and pre-edit freeze: confirm remote `develop`; inventory every required P3-P5 user-facing action; obtain Architect's consolidated replacement brief and independent visual red-team; create a materially different replacement artifact; freeze scope, non-goals, proof matrix, resource budget and first production-row write set for Architect GO | Exact baseline and branch evidence; complete action-to-surface inventory including project creation, Shared-workspace file creation/upload, chat creation/management and Settings; reviewed replacement brief; independent red-team verdict; Architect acceptance of the interactive artifact against complete functional coverage, current UX/design-system evidence, Web Console/ESP32 Cardputer feasibility and visual quality; reviewed first-row design/proof/write set before production | completed |
| P6-02 | Add the bounded API-profile and model-preset contract through existing settings, persistence, Device and Web owners | Measured NVS capacity; explicit count/length limits; selection/default behavior; malformed/full-storage failure; reboot persistence; Device/Web parity; exact cleanup and resources | completed |
| P6-03 | Add configurable authentication lifetime and independent multi-tab browser presence | Four exact lifetime choices; expiry and until-reboot semantics; aggregate visible-tab heartbeat; while WebServer is available, waiting within 30 seconds after the last heartbeat without auth loss; multi-tab correctness; blocking foreground request shown as Busy/unobservable and original timestamp evaluated at return without renewal; final-image startup rejection before login plus stale-token rejection through the shared clear owner | completed |
| P6-04 | Preserve active project, active view and drafts through the existing Web reconnect path | Same-address reconnect after transient disconnect and Python handoff; active project/view/draft restored; stale or missing state fails explicitly; no exact-scroll claim | pending |
| P6-05 | Bring the Web Console to the Architect-reviewed replacement direction, add explicit discovered-network Wi-Fi selection through the smallest reviewed existing-owner backend mapping, add Web Pending to complete Python source and back through existing P5 owners, and finish desktop/tablet/phone polish through the existing asset boundary | Every required Web capability reachable; explicit Wi-Fi scan/select/hidden-manual/connect states and other degraded states; complete-source review returns to the same Pending identity; stable-ID interaction checks; 1280, 900 and 390 px screenshots without overlap; soak and resource evidence | pending |
| P6-06 | Bring the 240x135 Device UI to the Architect-reviewed replacement direction through existing screen/input owners, including complete Python-source navigation and return to the originating Chat | Every required Device capability reachable; coherent navigation and compact states; Python source review returns to its originating Chat without changing approval state; provider/SD/optional-API degradation; no Web-only requirement leakage; device resources and latency | pending |
| P6-07 | Reconcile cross-surface behavior and run focused integration acceptance | Names/state/permissions consistent across Device and Web; profiles, sessions, presence, reconnect, SSH and Python full-source review/return boundaries interoperate; forbidden effects absent; exact-owned cleanup | pending |
| P6-08 | Establish and publish the stable Wi-Fi baseline and close Phase 6 | Full host/Device/Web regression; exact build options and binary hash; flash/RAM/heap/largest-block/stack/latency; screenshots; soak; cleanup; independent reviews; green CI; reviewed merge only to `develop` | pending |

## P6-01 reopened by Architect — 2026-09-15

At 2026-09-15T22:39:54+03:00, the new Architect explicitly reopens P6-01 following
the user's request for a complete personal prototype audit, the missing Device SD
indicator, a reported Web navigation-layout concern and explicit rejection of the
clinical cream/green palette. P6-01 is the sole active row. P6-04 is suspended as
`pending`; its five changed files, implementation, accepted code/build evidence and
uncompleted browser acceptance remain preserved, not discarded or declared failed.
P6-02 and P6-03 remain completed. No P6-04 proof, firmware/test edit, build or upload
runs while this reopened artifact boundary is active.

The reviewed artifact still has exact SHA-256
`D0B55029E1A1CFAE0CA596AC3AF3D1B52C470A2DFD070E7D6DB95E9469C2A16B`.
Personal Chromium inspection at 720x450 reproduced overlapping Shared-file list text:
the wrapped bundle name/metadata intersects the following entry. This contradicts
the prior final claim of separated collection rows at that size. Source comparison
also confirms that `ui.cpp::drawCarouselHeader` displays the existing SD-ready
indicator, while the prototype's `renderDevice` header emits only Wi-Fi and battery
for ordinary screens. The final P6-01 visual/functional acceptance is revoked for
these concrete defects; historical observations remain historical, not a current GO.

The user rejects the prior dominant clinical palette. The new visual brief must use
recognizable retro electronic-instrument composition: graphite instrument regions,
warm gray body surfaces, readable light labels and restrained amber interaction
accents. Reserve state colors for actual state. Preserve useful list/detail
architecture and every required action; add no decorative instrumentation, new
framework, backend simulation or broad aesthetic rewrite unrelated to this correction.

Architect owns the complete read-only Web/Device audit and one consolidated correction
brief: layout at desktop, tablet, phone and short/narrow sizes; all required
object/action routes, selection identity and displayed permission state; dialogs,
scroll/focus, degraded states and Device status. A prototype control count is not
functional proof. Explicit future production gaps remain separately owned by P6-05/06.

Phase 6 remains the sole implementation author. Before any artifact edits, freeze
the exact affected selectors/handlers, smallest proof and non-goals, then obtain
the required bounded independent pre-edit review. The allowed artifact correction
surface is the existing external prototype plus this trace and explicit user-scope
decisions in `ROADMAP.md`; production, retained tests, P6-04 files and device state
remain outside it. Do not rewrite working tests or construct another test runner.

### Architect consolidated correction contract — 2026-09-15

This current decision supersedes historical P6-01 visual GO, warm-light palette locks
and the standalone artifact's 184,320-byte ceiling. Unchanged ownership, product
contracts and explicit P6-05/06 gaps remain binding. The byte ceiling was assigned
as headroom over an earlier mock, without measured Device cost; the current artifact
has only two bytes remaining and its last correction removed formatting to fit.
Do not minify, delete functionality or add abstractions to satisfy that superseded
ceiling. Report before/after artifact bytes as diagnostic evidence. The artifact
budget remains one self-contained HTML/CSS/JS presentation, with no added dependency,
external asset/font/request, storage, timer, backend clone or persistent allocation.
Actual firmware flash/RAM/stack/latency acceptance remains in the production rows.

On the unchanged D0B55029 artifact, Architect personally observed:

- Shared-file rows at 720x450 shrink to 36 px while wrapped title/metadata extend
  into the next row. A bounded read-only visual audit found the same cause in SSH
  profiles: metadata y276.19..307.58 intersects the next title y294.08..310.08;
  Architect inspected that screenshot. Connected Terminal -> Remote files collapses
  its list to 4 px at 720x450 and 320x568 even after a scroll attempt. Architect
  inspected the narrow screenshot; a technically successful hit-test does not make
  the clipped names readable.
- `renderDevice` omits SD while production `ui.cpp::drawCarouselHeader` retains it.
  This is a prototype regression, not evidence of a failed physical card.
- Chat settings expose Ask/Ask/Allow/Ask/Off/Off/Off/Off, while Capability status
  renders every entry as Ask / Project policy. Device also has a hard-coded status
  snapshot. These are misleading presentation values, not an observed firmware
  permission bypass.
- Opening the second Web search source (ESP32 power management) opens the first
  source's M5Stack title and URL. The selected identity is not passed to the detail.
- Uploading a small valid UTF-8 `.yaml` file yields Binary / transfer-only and removes
  the editor, although the shipped text classifier and locked safe-text acceptance
  include YAML. The mock uses a narrower independent extension list. A further
  direct control check at 900x720 on the same SHA uploaded a 28-byte valid UTF-8
  `.txt`: it became Text / 0 B with an empty `cmFileEditor`. `genericConfirm`
  constructs text uploads from an empty string and never reads the selected File.
  This same Upload owner must preserve selected text content and byte count as well
  as classification; its correction adds no backend or editing engine.
- At 320x568, Device FileViewer has 106 px visible / 138 px content with hidden
  overflow; Down leaves the text and scroll position unchanged despite its page
  footer. FileEditor similarly clips 125 px into 106 px. SSH profile actions have
  113 px content in 106 px. All 88 Device catalog states were visually inspected;
  catalog selection proves presentation only, not navigation or execution.

The completed bounded Web audit covered four destinations, ten Settings categories,
manual Python and reachable dialogs at 1280x720, 900x720, 720x450, 390x780 and 320x568.
Its 52 presentation states per viewport are layout evidence only. Covered dialog
footers and enabled actions remained reachable, and Escape closed them. Do not
rewrite that working dialog boundary without a concrete changed-boundary defect.

Phase 6 shall make one coherent correction within existing owners:

1. Replace the rejected dominant cream/green with graphite/warm-gray instrument
   surfaces, readable light labels and restrained amber selection/action emphasis.
   Preserve browser appearance preferences and meaningful state distinctions. Keep
   navigation icons/labels aligned and legible, including the reported narrow rail;
   no decorative machinery, new font/asset system or new breakpoint family.
2. Correct collection item sizing and task/list scroll ownership so full filenames,
   metadata, selected SSH profiles and SFTP entries remain readable at short/narrow
   sizes. Audit all consumers of the affected existing list styles, not just Files.
3. Restore visible SD-ready/unavailable status through the existing Device header
   and presentation state. Retain the existing 240:135 logical display model; make
   selected rows and complete file content reachable through truthful Device keys.
   Do not substitute shrinking every font or scrolling the outside review page for
   usable content inside the Device screen. No editor/backend engine is requested.
4. Bind Web source detail to the chosen source; align uploaded safe-text presentation
   with the shipped classifier; show truthful raw/effective capability and origin
   values from the selected presentation record on Web and Device. Reuse existing
   state and helpers, with no parallel authoritative policy resolver or backend clone.
5. Freeze exact selectors/handlers and the smallest direct proof before edits, then
   obtain the one required independent pre-edit review. Prove changed interactions
   through real controls and capture all four Web destinations at the five sizes,
   all Settings/Device presentation screens and changed degraded states. Personally
   inspect text/row clipping, not only outer control boxes; catalog traversal alone
   never proves an action. No new retained harness or rewrite of repository tests.
6. Send Architect exact old/new SHA, scoped diff, observations, screenshots and any
   unverified boundary. Architect personally decides GO/STOP. P6-04 stays suspended
   and unchanged until this correction is accepted; full firmware release acceptance
   remains a later gate, not a claim made from this mock.

## P6-01 locked boundary

P6-01 is a pre-production phase-transition row. The prior task-owned Concept C visual-polish
artifact is rejected evidence only and is frozen without further iteration. The replacement must
start from Architect's complete P3-P5 user-action inventory and corrected compositional brief.
The later explicit user decision retains the prior warm-light identity: functional and geometry
correction does not authorize a wholesale aesthetic redesign or a different product mood.
P6-01 does not own firmware, Web production assets, generated headers, schemas, persisted values,
routes, tests, builds, uploads or Device state.

Production work and the P6-02 design freeze remain stopped until Architect supplies the consolidated
replacement brief and independent visual red-team result. The replacement must cover every required
P3-P5 user-facing action, explicitly including workspace/project creation, chat creation and
management, and the complete applicable Settings surface. No replacement detail may be invented
before that brief.

The later visual replacement additionally fails closed on generic AI-dashboard styling: purple/blue
gradients, glassmorphism, blur, glow, repeated interchangeable rounded cards or pills, sparkle/AI
ornaments, oversized empty hero regions, decorative pseudo-metrics, ambient or looping motion and
other template-like AI-console treatment are prohibited. The accepted language must be specific to
CardMind and Cardputer: a professional working tool with a clear list-detail hierarchy, useful
density, semantic status, recognizable hardware continuity, and expression through composition,
typography, solid color and shape. This criterion does not unfreeze visual work before Architect's
separate functional `GO` and consolidated design brief.

Before P6-01 can close:

1. Receive Architect's consolidated inventory of every required P3-P5 user-facing action, replacement
   brief and independent visual red-team result.
2. Freeze the replacement artifact's functional coverage, visual direction and explicit non-goals.
3. Produce one new bounded interactive artifact without iterating the rejected Concept C polish.
4. Verify all inventoried actions at representative desktop, tablet, phone and 240x135 Device sizes.
5. Obtain the required independent review verdicts and Architect's independent, evidence-backed
   acceptance of complete functional coverage, current UX/design-system applicability, constrained
   Web Console/ESP32 Cardputer feasibility and sufficient visual quality. No user choice is required.
6. After Architect acceptance, close and publish P6-01. Only after exact remote-SHA verification,
   activate P6-02, freeze its smallest production design, proof matrix, measured resource budget,
   non-goals and exact write set, then obtain Architect's separate explicit pre-edit GO.

The P6-01 repository write set is exactly `AGENTS.md`, `ROADMAP.md` and this traceability file. The
interactive artifact is task-owned outside the repository. Any production edit before the final
Architect GO is out of scope.

## Observed P6-01 kickoff evidence

**Started:** 2026-09-02T22:34:32+03:00.

- Authenticated GitHub MCP resolved remote `develop` to
  `fd9373aa93bd04e217b2e58c6a6ee75b80e3eaf8`; the immutable commit is the Phase 5 PR #3 merge.
- The local remote-tracking ref was fetched to the same SHA, and the Phase 6 branch was created at
  that exact commit. The starting tree is `a737175feadb384e860bdefa503d880e5bc54f1c`.
- The starting tracked worktree was clean. Only the three Architect-owned `.codex/agents` files were
  untracked, and the retained stash remained present and untouched.

## Rejected P6-01 visual and feasibility checkpoint

**Observed:** 2026-09-02T23:09:28+03:00.

- The task-owned artifact is
  `C:\Users\84vs1\.codex\visualizations\2026\09\02\01a06386-22d5-7833-bb82-40a4f499f52e\concept-c-visual-polish.html`.
  A no-index comparison against the canonical Concept C prototype reports exactly 322 inserted CSS
  lines and zero deletions. Both artifacts retain one script with SHA-256
  `8863FF9A606396B00D0DE5F61C3494A3CD8C3AEED7304F55765DAE3CB32A383A` and the same 54 IDs.
- Browser checks produced exact 1280x720, 900x720 and 390x780 Web captures with no horizontal
  overflow. Visible control minima were 38 px on desktop/tablet and 44 px on phone; the phone bottom
  navigation remained flush with the product edge. The Device screen remained exactly 240x135.
- Mock-local interaction checks passed for all four Web destinations, active-project visibility,
  retained draft, disconnect-before-profile-switch, mismatch blocking, keep-blocked, exact-host
  forget without automatic reconnect, explicit reconnect, SFTP open/close and the single live
  terminal. All nine Device cards appeared in order; NETWORK opened the existing Wi-Fi picker,
  degraded WEB CONSOLE remained selectable, and TOOLS reached the complete SSH menu, manual-terminal
  detail and live terminal. The browser console reported no warning or error.
- The independent visual-quality review initially stopped on two 10 px helper labels, semantic-color
  reuse in ordinary ornament and inexact scrollbar-bearing captures. The same bounded pass restored
  the labels to 12 px, made the ornament neutral and produced exact-size captures; the one permitted
  blocker verification returned `GO`.
- A separate fresh functional-feasibility review mapped the artifact to the existing single Web
  asset/embed/root/route owner, P4 SSH profile/terminal/SFTP owners, P5 same-address handoff, current
  settings/NVS path, session token, URL-hash/draft state and the existing nine-card Device producer,
  renderer and input dispatcher. It returned `GO`: no second framework, server, route family,
  storage subsystem, terminal or dashboard is required.
- Architect independently checked the checkpoint and the exact desktop/tablet/phone renders and
  found no hidden technical or scope debt: the artifact remained presentation-only, behavior and
  IDs were preserved, both bounded reviews were `GO`, and no production boundary was touched.
  Architect explicitly kept P6-01 active pending the user's visual evaluation.
- Source reconciliation confirms the remaining Phase 6 gaps rather than hiding them: production has
  one API/model configuration, a fixed 15-minute session, no browser heartbeat/presence contract,
  only partial hash/draft reconnect state and incomplete explicit provider/optional-API degradation.
  These remain owned by P6-02 through P6-07. Production behavior was not changed by this checkpoint.
- These review verdicts and Architect's visual acceptance were invalidated by the later STOP because
  they preserved an incomplete prototype rather than checking the complete required user-action
  inventory. They are retained only as historical evidence and cannot support P6-01 closure.

## P6-01 Architect STOP

**Observed:** 2026-09-02T23:17:00+03:00.

- The user rejected both the palette and layout and identified concrete functional omissions:
  workspace/project creation, chat creation and management, and substantial Settings coverage.
- Architect issued `STOP`, invalidated both prior review `GO` verdicts and the earlier Architect
  visual acceptance, prohibited P6-01 closure, P6-02 freeze, production edits and further iteration
  of the existing polish artifact, and required a complete P3-P5 action inventory plus an independent
  visual red-team before issuing a consolidated replacement brief.
- Architect's source inventory found 188 unique element IDs in the shipped Web Console and 54 in the
  rejected mock, with zero exact overlap. The mock exposed only three unnamed chat selectors plus
  Send, represented Files as a static list and reduced Settings to session/browser/theme/device-status
  text; it provided no workspace/project creation, chat creation or project/chat CRUD and no
  substantial Settings controls. This disproves the checkpoint's stable-semantic-ID and
  functional-feasibility claims as production-parity evidence.
- The rejected artifact and its captures remain untouched as rejected evidence only. No production
  file, production test, build, upload or Device state was changed by the rejected checkpoint.
- P6-01 remains the sole `in_progress` row. Its active-work clock is paused while awaiting Architect's
  consolidated brief and red-team result; all production rows remain `pending`.

## P6-01 replacement coverage contract

**Received:** 2026-09-02 after the Architect STOP.

The rejected Concept C is not a base for iteration. Its mock-only information architecture, palette,
layout, 54-ID namespace and simulated behavior cannot be preserved as acceptance evidence. Production,
tests, builds and Device state remain frozen throughout this coverage gate.

Vocabulary is locked as follows:

- A **Project** is the user-created context with CRUD, settings, chats, shared-file links and bundle
  import/export.
- The **Shared workspace** is the single existing SD-backed `/assistant/files` area. It is not a
  named or separately created object; users create or upload files and link them to projects.
- The **Python workspace** is the existing startable manual runtime. It is not multi-workspace CRUD.
- Global creation is **New project**; Files exposes **New text file** and Upload; Python exposes Start
  when unavailable. A generic `New workspace` product object is forbidden.

Before visual styling, P6-01 must map each required function to Web (`W`), Device (`D`) or both
(`W+D`), an exact reachable screen/control, its states and its existing production semantic ID or an
explicit one-to-one mapping. The minimum functional inventory is:

1. **Global Web shell/session (`W`)** — login; authenticated state; lock/logout; explicit Console
   close/end; active-project selector and New project; persistent Chat, Workspace/Files, Terminal and
   Settings destinations; applicable Device, Wi-Fi, SD, provider/model, Python and pending/activity
   status refresh; the four exact P6 session lifetimes; multi-tab heartbeat/last-tab behavior;
   same-address reconnect preserving active project, active chat/view and drafts including Python
   handoff return; responsive desktop/tablet/phone navigation; no PWA.
2. **Projects (`W+D`)** — bounded list, create, select/open, rename, duplicate, archive/restore,
   delete, bundle export/import; instructions, model override, context budget, output-token override,
   auto-compact, optional SSH-profile ceiling and per-capability policy ceilings; shared-file inspect,
   link and unlink; explicit empty, loading, error and archive states.
3. **Chats and conversation (`W+D`)** — current and archived bounded lists, create/select and load
   more where supported; message history and streaming response; send, Stop and retry; model/context/
   capability and source/details visibility; compact/summary and full/archived history; chat
   instructions, model override, optional SSH ceiling and capability ceilings; supported rename,
   pin/unpin, archive/restore, duplicate, clear and delete; Markdown and project-bundle export/import;
   Auto, No tools, Web, Files, SSH and Python composer choices, next-output override and one-turn
   instructions; preserve draft and selected chat across destination changes and reconnect.
4. **Shared workspace/files/QR (`W+D` according to existing owners)** — real bounded SD directory
   listing/navigation with more/previous where supported; text open/read, bounded edit/window
   navigation, save, save copy/new text file, rename and delete; Web upload/download and project/chat
   bundle import; active-project link/unlink state; shipped Device find/bookmark/read-aloud/copy;
   text-or-file QR show/close; distinct missing, full, read-only, corrupt, removed-during-operation and
   replaced SD states plus replacement confirmation; no named-workspace CRUD.
5. **SSH profiles/security/terminal/SFTP (`W+D` according to shipped controls)** — at most five
   profiles with capacity, create, select/default, edit and delete; name/host/port/user/auth mode,
   write-only password/passphrase and private-key install without secret display/export; exactly one
   terminal with connect, unknown-host trust, mandatory changed-key block, exact-host forget, input,
   resize, streamed and bounded output, clear, disconnect/stop and supported fullscreen; existing SD/
   log/download behavior; existing SFTP navigation/file operations and controlled workspace-to-remote
   or remote-to-workspace transfers with explicit endpoints, overwrite denied by default,
   confirmation, cancel and normal error outcomes. Profile mutation remains locked while terminal,
   trust or mismatch state owns the selected profile; key-capacity failure preserves the prior
   binding. Automatic reconnect and reconnect schedulers, terminal tabs and a new SSH framework are
   forbidden, while explicit Connect after successful exact-host forget remains valid. The model
   surface exposes exactly `sftp_list`, `sftp_read`, `sftp_write` and `sftp_move`, plus the five fixed
   Safe Actions logs, service state, containers, disk and processes, through Chat, Pending and
   Activity rather than a separate application; arbitrary `ssh_command` remains mutating.
6. **Permissions/pending/audit (`W+D`)** — global master policy and defaults for new chats across Web
   search, Web fetch, Files read, Files write/delete, SSH read, SSH mutate, SFTP read/write and Python
   write/run; Project and Chat Inherit/Off/Ask/Allow ceilings plus selected SSH-profile availability/
   ceiling; composer intent cannot elevate broader policy and may select any W/F/S/P subset. Pending
   preview remains typed rather than exposing generic arguments: bounded file diff, exact SSH command,
   Python full-source route, or tool-and-reason-only generic projection, with stale authority explicit;
   rebooted pending exposes Acknowledge only. Allow once, Allow for chat only for an ordinary policy
   Ask, Deny and Acknowledge remain bounded by mandatory confirmation; activity/audit exposes tool,
   coarse target, status, duration, output bytes and optional SSH exit status plus cooperative cancel;
   raw/effective/source text accompanies compact W/F/S/P state. No duplicate policy engine,
   chain-of-thought view or configurable audit retention is allowed.
7. **Settings/providers/device controls (`W+D` according to existing owners)** — OpenAI-compatible
   base URL, secret key, default model and refresh; bounded P6 API profiles/model presets sized from
   measured NVS; global instructions and per-chat history quota; Wi-Fi SSID/password/connect state;
   STT, Web search and TTS endpoint/model/voice/key removal plus autoplay and volume; brightness,
   screen sleep, keyboard repeat and power profile; shipped Web surface style, compact density,
   reduced motion, terminal wake and diagnostic-metrics preferences. Controls require validation and
   save/apply/error states; telemetry is labelled status, never presented as a setting.
8. **Python (`W+D`)** — existing manual runtime readiness and Start; existing one-shot model path
   from Chat through mandatory path/size/SHA-256 and full-source approval, with an explicit privileged
   no-sandbox warning, then handoff to stdout/stderr/exit on the originating chat and same-address
   return/reconnect. The prototype must distinguish success, exception, normal reset, watchdog/power
   loss, effects-unknown, exactly-once attachment/no replay and canceled-before-runnable-staging. No
   second workspace, package manager, jobs, queue, scheduler or Python framework.
9. **Diagnostics/degraded states (`W+D`)** — live metrics and diagnostic export through existing
   owners; explicit provider/model, optional STT/TTS/search, Python image/runtime, Wi-Fi/session, SD
   and SSH-profile absence/unavailability; loading, empty, validation, connector failure,
   cancellation and timeout where existing contracts require them; distinct Browser connected,
   Waiting and authentication-expired states; SSH disconnected/failed/mismatch; and Python ready,
   unavailable and effects-unknown. No contradictory hard-coded ready/connected labels.
10. **Device 240x135 navigation (`D`)** — preserve all nine established destinations: Projects
    (projects, chats, settings/actions), AI (model/API, instructions, master/default policies,
    pending, activity), Voice (capture/transcription/playback and settings), Network (2.4 GHz scan,
    select, password, connect/save), Files (shared-area browser/editor/import/link), Web Console
    (start/address/session/Python/API and Wi-Fi entry), Device (display/power/quota/services/update/
    diagnostics), Tools (notes/checklist/timer/calculator/QR/SSH) and Help (controls/about/support).
    Tools remains the direct-user utility and SSH home rather than the LLM-permission home. Device
    keeps arrow navigation without requiring `Fn`, accessible state text, its own nested-screen model
    and explicit degraded states rather than cloning Web.

Canonical reconciliation narrows three ambiguous brief phrases without reducing required behavior:

- Device chat-bundle import remains removed because the retired control wrote legacy
  `/assistant/chats`; project-bundle import/export is the portable cross-surface path, while any
  retained chat import remains only on its existing owner.
- `No reconnect` means no automatic SSH reconnect or scheduler, not a ban on the explicit user
  Connect action after successful exact-host forget.
- `Full pending preview` means the complete safe typed preview applicable to that action, never a
  generic dump of arguments or secrets.

The ordered replacement gates are:

1. Deliver the complete coverage matrix and one neutral/grayscale low-fidelity IA prototype before
   any visual-polish layer.
2. Use actual production semantic IDs for existing Web controls or retain an explicit one-to-one
   mapping; add IDs only for exact P6 additions, never using the rejected `cm-*` namespace as proof.
3. Make prototype reachability and state changes interactive, label simulated data as prototype data,
   avoid contradictory readiness, and never use inert controls as evidence.
4. Independently red-team the matrix against ROADMAP, P3/P4/P5 traces, production routes/assets and
   Device menus; require Architect's personal coverage review before styling.
5. Only after coverage `GO`, create a materially new visual composition. The rejected dark teal,
   cyan and salmon palette, glow/gradient/grid, empty left rail, nested-card layout and mobile stacking
   are prohibited rather than polish targets.
6. Independently red-team the later visual hierarchy, responsiveness and accessibility at 1280x720,
   900x720, 390x780, 200% text zoom and Device 240x135.
7. Report omissions or conflicts exactly; never silently defer, invent or expand functions.

## P6-01 visual-direction STOP after coverage review

**Observed:** 2026-09-02T23:56:23+03:00.

- Architect personally reconciled the complete coverage matrix against the canonical sources and
  issued a coverage-matrix-only `GO`; this did not approve an artifact, palette, styling,
  production work, P6-02 or P6-01 closure.
- The task-owned `p6-01-neutral-coverage-ia.html` is frozen only as a functional coverage and
  wireframe reference. Its monochrome presentation was rejected as visually exhausting and must
  not be presented as the design, polished further or used as a base that is merely recolored.
- Architect issued `STOP` on further artifact work and required a bounded independent research pass
  over authoritative current sources for professional AI/chat, files, terminal and settings
  consoles, responsive navigation, information density, color hierarchy and compact 240x135 Device
  UI. The next deliverable is a source-backed set of patterns, anti-patterns and two or three
  materially distinct directions mapped to the verified CardMind IA.
- Production, tests, builds, uploads and Device state remain frozen. P6-01 remains the sole
  `in_progress` row.
- The user then clarified that the matrix and neutral IA are the immutable functional baseline:
  later visual work may change composition and presentation but may not drop or assume equivalence
  for any function. Before proposing visual directions, the task must independently validate every
  matrix row against the actual prototype for a reachable control or screen, required state variants,
  exact production ID or explicit P6-ID mapping, correct Web/Device ownership and absence of inert
  proof controls. Any omission is `STOP`; retain localhost or screenshot evidence usable by Architect.

## P6-01 functional-baseline audit and SD ownership correction

**Observed:** 2026-09-03T01:37:56+03:00.

- The earlier coverage-matrix-only `GO` and the subsequent candidate SHA-256
  `0A03AF411D4BC26915467DAC769303B585DDCB14C045A4F52A6A333F8054149B` are revoked as functional
  acceptance evidence. Architect found that their SD scenario text covered Projects, Chats and
  Shared files while the runtime guards covered only Shared-file handlers; Project/Chat reads and
  mutations therefore remained reachable in contradictory degraded states.
- The correction remains entirely inside the task-owned neutral artifact. One `sdMode` access owner
  now governs Project/Chat reads, writes, selection visibility and an active response stream in
  addition to the existing Shared-file guards. Missing, corrupt, removed and unconfirmed-replacement
  modes disable Project/Chat selectors, replace the chat content with an explicit unavailable state,
  and reject representative reads and writes. Full and read-only modes preserve selection, loading
  and export reads while rejecting Project/Chat creation, settings/metadata mutations, message send,
  compact, retry, destructive actions and project-bundle import before any dialog or state change.
- Browser observations verified the forbidden effects directly. In each read-unavailable mode,
  `Load more projects` and `New project` reported the exact SD reason, retained the three-item project
  count and opened no dialog. In both full and read-only modes, project switching and pagination
  remained available; an unsaved draft was not persisted across selection changes; New project,
  New chat, Send, Compact, Retry, Rename project and Clear chat retained their prior counts, messages,
  title and context meter; project/chat exports and text-file reads remained available; project-bundle
  import failed explicitly. Removing the SD during an active response replaced `Streaming` with a
  typed failure and never produced `Response saved`. Replacement confirmation and a return to Ready
  re-enabled selectors, project/chat creation and message streaming.
- The corrected functional candidate is
  `C:\Users\84vs1\.codex\visualizations\2026\09\02\01a06386-22d5-7833-bb82-40a4f499f52e\p6-01-neutral-coverage-ia.html`,
  SHA-256 `F2AD0CB39BFAB1424262997D2481C43F69838175029553FE999BECDACBE94EBD`, 164,423 bytes and
  1,983 lines. It retains 76 matrix rows across ten domains, 231 unique IDs, one syntax-valid script,
  no unresolved literal queried ID, no unhandled ID-bearing button and no generic Device fallback.
  The current review server is `http://127.0.0.1:57263/`.
- This evidence corrects the residual SD contradiction only; it does not approve visual styling,
  production work, P6-02 or P6-01 closure. The corrected hash still requires the bounded independent
  blocker verification and Architect's new personal browser `GO`.

## P6-01 narrowed blocker correction and acceptance-owner update

**Observed:** 2026-09-03T02:03:49+03:00.

- The user assigned visual-applicability acceptance to Architect without requiring another user
  choice. Architect may issue the later visual `GO` only when the same candidate proves complete
  functional coverage, applicability of current 2026 UX/design-system patterns, feasibility for the
  constrained Web Console and ESP32 Cardputer 240x135 surfaces, and sufficient visual quality.
- The independent narrowed reviewer issued `STOP` on candidate
  `F2AD0CB39BFAB1424262997D2481C43F69838175029553FE999BECDACBE94EBD`. Its 76-row structure and 71
  rows remained clear, but five reachable contradictions survived: the Project/Chat detail drawer
  leaked during unreadable SD states; global or project-bound provider unavailability did not block
  every model operation; Python unavailable did not own manual Start; Python return discarded a live
  unsent draft; and chat-list mutations leaked between projects through one global DOM inventory.
- The task-owned correction closes only those five owners. Unreadable SD states close and hide the
  detail drawer. One model-operation guard covers Send, Retry and Compact for both global-provider and
  saved-project-profile unavailability, and provider loss terminates an active response with an
  explicit failed outcome. Python has one availability state shared by its summary, detailed pane,
  manual Start and Python-intent Send; Start saves the originating context before handoff. Each
  project now owns its chat inventory and selected chat; create, pagination, rename, flags,
  duplication, deletion and project lifecycle synchronize only that project's inventory.
- Browser verification observed all five forbidden-effect boundaries. The four unreadable SD modes
  hide both chat content and the open detail drawer. Unavailable global and project API states retain
  message count, draft, one-turn controls and context meter while Send, Retry and Compact fail; a
  provider transition replaces `Streaming` with an explicit failure and never later saves it. Python
  unavailable retains the draft and history while both Start and Python-intent Send fail, whereas a
  ready Start restores the exact pre-handoff draft on return. Creating and loading chats in Field
  notes left Lab setup unchanged; creating then deleting a Lab setup chat left Field notes unchanged.
  New, duplicated and deleted projects initialized, cloned and removed only their owned chats.
- The corrected candidate is the same task-owned artifact, SHA-256
  `52DB1280015AFA0CCA152CA2695780976C02CE2A4C6386E0BB1F448C052F0310`, 171,507 bytes and 2,100
  lines. It retains 76 seven-cell matrix rows across ten domains, 231 unique markup IDs, 166 unique
  literal queried IDs with none missing, 85 handled ID-bearing buttons, one syntax-valid script and
  no generic Device fallback. Browser reflow remained contained with no horizontal offender at
  1280x720, 900x720 or 390x780. The live review server is `http://127.0.0.1:65428/`.
- Visual styling, production code/tests/build/device work, P6-02 and P6-01 closure remain frozen. This
  exact hash now awaits the reviewer's one blocker-verification verdict and Architect's personal
  browser `GO` or concrete `STOP`.
- The same independent reviewer used its one blocker-verification pass and returned `GO` on exact
  SHA-256 `52DB1280015AFA0CCA152CA2695780976C02CE2A4C6386E0BB1F448C052F0310`: all five blockers are
  resolved, the structural counts match, and no correction-caused regression was found in the 71
  rows cleared by the prior pass. Architect's personal functional browser verdict remains required.

## P6-01 functional GO and consolidated visual brief

**Observed:** 2026-09-03T02:16:35+03:00.

- Architect personally exercised the five corrected boundaries and representative previously
  cleared paths, then issued `FUNCTIONAL GO` on exact SHA-256
  `52DB1280015AFA0CCA152CA2695780976C02CE2A4C6386E0BB1F448C052F0310`. Its single script block has
  SHA-256 `0F0FD1D4E0F7D172288B44434371D76740E6C5860B7B8EED1F2F1B3EA4C162A6`; this is the frozen
  behavior baseline for the visual candidate. Architect additionally traversed all nine Device
  destinations, 67 items and 118 detail pages. The 76-row contract, IDs, controls, state graph and
  handlers are accepted and must survive visual work.
- Architect's consolidated direction is one product-specific `CardMind precision field console`,
  not a generic AI dashboard or retro-terminal pastiche. Expanded Web uses one labeled primary rail,
  a contextual list where needed, one dominant work canvas and only an owning contextual inspector;
  medium keeps the rail and dominant pane with temporary list/inspector panels; compact is one pane
  at a time with labeled navigation and an explicit Back path. Chat must foreground active Project
  and Chat, conversation and composer; Files remains list-detail; Terminal remains one terminal with
  profile/SFTP context; Settings remains a section list with coherent forms rather than a card wall.
- The locked visual system is a graphite shell, warm light working canvas, solid surface tiers and
  one measured burnt-orange hardware-derived accent. A restrained cool secondary may identify a
  distinct interaction role; green, amber and red are semantic only. Geometry mixes modest work
  surfaces, tighter controls and square technical output; typography is small and disciplined with
  monospace confined to code, paths, terminal and machine output. Purple/blue gradients,
  glass/blur/glow, equal rounded cards, pill soup, AI sparkle/robot/brain ornaments, empty hero areas,
  fake metrics, ambient motion and raster or external assets remain prohibited.
- The 240x135 Device frame is an independent handheld instrument with a stable title/status band,
  bounded task/list/detail region, conspicuous keyboard focus and a bottom key legend/Back affordance.
  It retains all nine destinations and representative deep screens using one RGB565 canvas, existing
  fonts, solid fills/borders, lines and optional 8x8 procedural icons, with at most five menu rows and
  event-driven redraw. It must not imply a framebuffer, widget tree, raster asset, blur, alpha,
  continuous animation or persistent allocation.
- Visual acceptance requires screenshots and interaction evidence at 1440x900, 1024x768, 390x844,
  320x568 and 200% text size; all nine Device homes plus representative Project, Chat, Files,
  SSH/SFTP, Pending, Settings, SD and fatal frames; contrast, targets, keyboard/focus, dialog return,
  reduced-motion and static external-resource/animation/blur checks; a bounded embedded-size estimate;
  and one fresh visual red-team with at most one consolidated correction pass. Production, P6-02 and
  row closure remain frozen until Architect issues a separate visual `GO`.

## P6-01 visual-source constraints

**Observed:** 2026-09-03T02:16:35+03:00.

- W3C WCAG 2.2 (`https://www.w3.org/TR/WCAG22/`) supplies the acceptance floor rather than an art
  direction: 4.5:1 normal-text and 3:1 large-text contrast, 3:1 meaningful non-text/focus contrast,
  200% text resize without lost content or function, 320 CSS px reflow without two-dimensional
  scrolling except genuinely two-dimensional content, keyboard operation without traps, visible and
  not-entirely-obscured focus, non-color state cues and 24x24 CSS px AA pointer targets or a listed
  exception. CardMind's approximately 44x44 touch target is a stricter product goal, not an AA claim.
- Material 3's current canonical list-detail guidance
  (`https://m3.material.io/foundations/layout/canonical-examples/list-detail`) directly supports one
  pane plus Back in compact layouts and simultaneous list/detail only when space permits. Its
  navigation-rail guidance (`https://m3.material.io/components/navigation-rail/guidelines`) supports
  a labeled rail at medium and larger widths and a navigation bar at compact widths. Material `dp`,
  Fluent breakpoint names, CSS pixels and Apple points are not interchangeable; the candidate uses
  its own content-driven Web ranges: compact through 719 CSS px, medium 720-1179 and expanded 1180+.
- Fluent 2 layout and color (`https://fluent2.microsoft.design/layout` and
  `https://fluent2.microsoft.design/color`) support adaptive spacing/grids, reserving the largest
  region for primary work, approximately 44x44 Web touch targets, neutral structural surfaces,
  sparse shared accents and semantic status colors paired with another indicator. They do not
  prescribe the rail, inspector, warm palette or solid-only CardMind art direction.
- Apple's Generative AI and accessibility guidance
  (`https://developer.apple.com/design/human-interface-guidelines/generative-ai` and
  `https://developer.apple.com/design/human-interface-guidelines/accessibility`) supports explicit
  progress/failure, retained user control, clear AI capability/limitation disclosure, enlarged text,
  non-color state cues and reduced repetitive/automatic motion. It does not require or prohibit
  sparkle, gradients or other generic AI motifs; those prohibitions remain the user's and
  Architect's product-specific decision.
- MDN responsive-design and `prefers-reduced-motion` guidance
  (`https://developer.mozilla.org/en-US/docs/Learn_web_development/Core/CSS_layout/Responsive_Design`
  and `https://developer.mozilla.org/en-US/docs/Web/CSS/Reference/At-rules/@media/prefers-reduced-motion`)
  supports a narrow single-column base, adding columns at content-driven breakpoints and removing,
  reducing or replacing nonessential motion. The candidate therefore uses no animation or transition
  at all; reduced-motion behavior is identical rather than a separate visual mode.

## P6-01 first styled-pass visual STOP

**Observed:** 2026-09-03 after the functional GO.

- Architect issued `VISUAL STOP` on the first `CardMind precision field console` styling pass. This
  does not revoke the functional baseline or authorize changes to its script, IDs, handlers or state
  graph. The task must not request visual GO from a patch of only the reported screenshots; it must
  audit every screen and component family before freezing one corrected candidate.
- API-profile fields and their creation/destructive actions lacked vertical rhythm, grouping and
  action hierarchy; Delete was not safely separated. The Wi-Fi pane exposed only a manual SSID field,
  dropping the locked Device scan/select expectation from this Web surface. Before correction the
  task must inventory the existing scan, protected-portal and Web owners, then reuse the smallest
  existing boundary: visible discovered-network selection, an explicit separate hidden/manual SSID
  path, password and connection state, with no speculative route or framework.
- Master access rendered sixteen large native selects as a sparse, poorly scannable table without a
  strong Off/Ask/Allow representation. The correction must compare a compact segmented/radio pattern
  against deliberately styled native selects using keyboard operation, 320 CSS px reflow, 200% text
  size and embedded-byte cost. The composer/options family also failed: controls clipped visually,
  the output-token field detached from intent, axes/heights diverged and unexplained empty space
  remained below the conversation.
- The Device home carousel remains rejected without destination pictograms. The correction must
  compare (a) existing 8x8/line icon + short label + concise status with adjacent destination peek,
  (b) an icon-led compact destination card and (c) a compact icon/list alternative, then select one
  existing-primitive approach. All nine destinations, order and arrow/Enter/Back behavior remain
  immutable; no new bitmap, theme, widget or allocation owner is allowed.
- The required self-audit inventory is `defect → governing rule → chosen correction → affected
  screens`. It covers all forms, buttons, selects, destructive actions, tables/lists, composer,
  panels, dialogs, degraded/empty/error states and 1440x900, 1024x768, 390x844, 320x568 and 200% text
  layouts. Every one of the 76 required action/state rows must remain reachable behind a visible
  control. The restrained field-console surface language may remain; CRT/scanlines, all-monospace,
  low-contrast amber, fake-terminal labels and generic AI decoration remain prohibited.
- The task-owned artifact currently has SHA-256
  `1645F105B659EE887A9A5E254D0BC60A7CF61B75FE631636233844F26902AE5A`, 231 unique IDs and the
  unchanged accepted functional-script SHA-256
  `0F0FD1D4E0F7D172288B44434371D76740E6C5860B7B8EED1F2F1B3EA4C162A6`. This is unfinished STOP
  evidence, not a frozen candidate. Production, P6-02, tests, builds, uploads and Device state remain
  frozen.

## P6-01 functional-GO revocation and semantic re-audit

**Observed:** 2026-09-03 after the first styled-pass visual STOP.

- Architect revoked the earlier functional `GO`. Source inspection proved that `#fullSsh` only
  changes its own label and the status text; it does not enter a fullscreen layout, alter terminal
  geometry or update the displayed rows/columns. Coverage row 5 nevertheless claimed input, resize,
  output, clear and Web fullscreen. The earlier ID/listener and handled-button counts were therefore
  invalid behavioral proxies and cannot support any row-level acceptance.
- Further visual correction is frozen until all 76 rows receive a semantic re-audit. Each required
  observation and forbidden effect must be exercised or traced to a real state transition. Every
  visible control is classified as `real interactive simulation`, `cosmetic/no-op`,
  `incomplete-state` or `navigation-only`; only the first classification can prove a claimed effect.
  Authoritative production semantics govern any correction. The accepted script hash and ID/state
  inventory are reference points, not permission to preserve a false simulation.
- Terminal correction must keep exactly one terminal, actually enter and exit fullscreen, change its
  geometry and displayed row/column state coherently, and provide an explicit keyboard/touch resize
  alternative rather than depending only on a drag handle. SSH/SFTP visual correction, after the
  semantic audit, uses progressive disclosure without dropping existing fields or IDs: normal
  context is the selected-profile/trust/connection summary plus New/Edit; New/Edit replaces it with
  the full form and explicit Save/Cancel with secrets, key install and separated Delete; SFTP is a
  distinct related Files mode rather than content stacked under the profile editor. The terminal
  stays dominant; medium/compact context remains temporary with explicit Back.
- The Files correction belongs to the same later consolidated pass. It must distinguish collection
  creation/import from selected-file Open-or-Enter, Download, Rename and Link/Unlink; separate the
  confirmed destructive Delete; reconcile whether selection already opens before retaining an Open
  control; avoid arbitrary action wrapping; and remove phase/proof labels from product copy. IDs and
  behavior require one-to-one mapping, not deletion behind an overflow affordance.
- The visible plan returned P6-01c to `in_progress`; independent functional review and the entire
  visual pass are pending again. No production, P6-02, test, build, upload or Device action is
  authorized by this re-audit.

## P6-01 semantic-proof boundary and source inventories

**Observed:** 2026-09-03T02:47:28+03:00.

- Architect narrowed the corrective proof to UI-contract behavior, not a fake backend. The complete
  matrix plus exact reachable screen/control/state mapping may prove exhaustive coverage. Navigation,
  selection, create/edit disclosure, menus, dialogs/focus return, Wi-Fi scan/select/manual entry,
  terminal resizing/fullscreen, responsive pane transitions and representative confirmation flows
  must be genuinely interactive. Pending, SD, provider, SSH trust/mismatch, reconnect/draft and
  Python handoff must enforce their legal transitions and forbidden effects. A correctly placed
  control with a visible typed outcome is sufficient for a stateless external effect such as export,
  download or refresh; no file, network or firmware backend belongs in this artifact.
- Device `openWifiPicker` uses the shipped scan owner, sorting, protected/open indication,
  selection, password and connect/save states. The protected provisioning portal also owns a
  scanned-network select plus a separate hidden-SSID field and write-only password. Before the
  latest user feedback, the production main Web Console intentionally exposed only manual
  `wifiSsid` and write-only password; no main-Web discovered-network data route was found. The user
  has now explicitly added discovered-network selection to the main WebUI. P6-01 models explicit
  scan/select and a separate hidden/manual path locally; P6-05 owns proof of the smallest safe
  production backend mapping that reuses `wifi_networks` and provisioning logic. A narrow route or
  state field may be justified there, but no route family or background scanner is authorized.
- The Device artifact preserves the exact nine-destination order and all 67 items and 118 detail
  pages, and its six pointer buttons can reach every page. That proves the static catalog only. There
  is no keyboard dispatcher, no action/state identifier and no operation invocation: Enter on a
  detail page merely advances to another static page, including where the copy claims confirm,
  install, overwrite, pause or delete. SD, Pending, SSH, Python, browser-presence and provider states
  are separate from the Web-side state owners; a false firmware `VERIFIED` page is reachable without
  its prerequisites; fatal/status behavior is absent. Until corrected, Device operation claims are
  `navigation-only`, with informational About/Back the sole meaningful exception.
- Device visual implementation may reuse one static procedural line icon per destination, the full
  selected label, a restrained indexed/neighbor cue and the existing title/status/key bands. The
  shipped UI already has a complete nine-icon procedural line set and ordered position marks. The
  literal `no framebuffer` wording in the earlier visual brief is inaccurate: production owns one
  persistent full-display `LGFX_Sprite`, whose default RGB565 storage is about 64,800 bytes at
  240x135. The actual constraint is no additional framebuffer, bitmap asset, widget system,
  persistent allocation or animation owner. The existing animated rounded carousel is not the
  selected direction because it carries six intermediate redraws and visual language rejected by
  the field-console brief.

## P6-01 complete semantic/component audit and coherent rebuild freeze

**Observed:** 2026-09-03 after Architect's consolidated systemic `STOP`.

- Two fresh read-only audits independently rejected unfinished artifact SHA-256
  `1645F105B659EE887A9A5E254D0BC60A7CF61B75FE631636233844F26902AE5A`. Across Web rows 1-66,
  only rows 4, 7, 36 and 46 already supplied sufficient interactive semantics. Seven rows were
  status-only/no-op, six were Device-owned or non-goal navigation mappings, and the remaining 49
  were incomplete. The strongest false claims were policy persistence/effective precedence,
  visible QR presentation, terminal fullscreen/geometry and large-output ownership, main-Web
  Wi-Fi discovery, browser-local preferences, and Python approval/origin handoff. The Device audit
  separately classified the 9/67/118 catalog as exhaustive navigation evidence but not operational
  behavior.
- The action audit found a systemic ownership defect rather than isolated styling: collection,
  selected-object, operation, rare and destructive controls were repeatedly mixed; Stop/Cancel and
  inverse actions remained visible outside their legal state; Settings Save was placed inside the
  category navigation; dialogs closed after failed validation and native Escape bypassed their typed
  cancel path; compact inspectors could hide the focused control without returning focus. Required
  labels, state-specific status cues, inline errors, role-based messages, binary/bundle file states,
  44px targets, long-text wrapping and compact navigation also failed across component families.
- Architect therefore ordered one coherent rebuild of the same task-owned artifact, not another CSS
  override or a sequence of screenshot patches. The retained material is the exact 76-row coverage
  vocabulary, proven project/chat isolation and SD, SSH mismatch/forget and pending helpers, the
  one-terminal/four-destination/context-pane concepts, and the restrained graphite/warm/rust visual
  direction. The two conflicting style systems, permanently expanded forms, handled-ID proxy and
  static Device prose as behavioral proof are rejected implementation material.
- The frozen rebuild uses one DOM/CSS system and nine bounded patterns: persistent shell/navigation;
  collection-list-detail; selected-object action ownership; New/Edit/Save/Cancel disclosure;
  accessible confirmation/focus return; stored layered policy with effective/source summary;
  single-operation state; shared degraded/handoff identity; and an icon-led 240x135 Device catalog
  with only representative interactive risk/layout flows. Evidence levels are explicit: `A` is
  exhaustive reachable mapping, `B` is real layout/interaction behavior, `C` is real legal-state and
  forbidden-effect behavior, and `D` is a correctly placed external/stateless action with a typed
  outcome. The rebuild will not simulate storage, firmware, networking or every production action.
- The production and test write set remains empty. The artifact write is only
  `C:\Users\84vs1\.codex\visualizations\2026\09\02\01a06386-22d5-7833-bb82-40a4f499f52e\p6-01-neutral-coverage-ia.html`;
  canonical observations remain in this trace and the explicit main-Web Wi-Fi scope decision in
  `ROADMAP.md`. No P6-02 design or production owner is unfrozen.
- The repository-root untracked file literal `m[1])` is zero bytes and was created at
  2026-09-03T00:17:55+03:00, but no evidence binds it to this task or an exact-owned P6 action. It is
  preserved unchanged; cleanup is intentionally not claimed.

## P6-01 whole-artifact rejection and consolidated correction package

**Observed:** 2026-09-03 after the coherent-rebuild checkpoint.

- Architect issued an exact whole-artifact `STOP` on task-owned candidate SHA-256
  `BE0114D1D799F5342EFFE2ACBC5B0A4E79CEC78904EEA86B637C48C9FD0029EB`. This is a distinct rejected
  checkpoint from the earlier `1645F105B659EE887A9A5E254D0BC60A7CF61B75FE631636233844F26902AE5A`
  visual STOP. The rejected bytes are frozen as evidence; they cannot support functional, visual or
  P6-01 closure claims.
- Direct load proved that the candidate had no bootstrap: the Chat collection advertised two
  messages while `#messages` was empty; the Device screen, Device map and 76-row coverage body were
  empty; and the scenario selector plus Reset control had no handlers. The artifact was an HTML
  fragment without a doctype, UTF-8 declaration or viewport, so the browser selected Windows-1251
  and corrupted multiplication signs, middle dots, minus signs and arrows.
- The reviewer-state selector was decorative and its authentication, collection, SD, reconnect,
  SSH-mismatch, Python and diagnostics states were not reachable. Initial policy controls were not
  synchronized from the model before Save. Manually assigned A/B/C/D labels, static IDs and
  screenshots therefore did not prove the claimed state transitions.
- Architect reproduced shared semantic defects: SSH-profile availability did not ceiling effective
  policy; multi-intent evaluation stopped at the first `Ask`; pending consumption used an identity
  broader than one operation; SD gating missed applicable Project/Chat/File paths and did not always
  restore editability; several Settings/profile fields did not round-trip; destructive lifecycle
  paths could leave stale operation UI; final-file deletion could dereference a missing selection;
  QR output was a pseudo-random non-QR grid; and Device representative flows advanced storyboard
  pages while claiming legal-state proof.
- The compact composition failed as one system: Project and Chat settings were stacked into a
  3226-pixel undifferentiated inspector; responsive policy labels and selects became detached;
  action hierarchy collapsed; 1024-pixel Settings controls overlapped their heading; compact
  terminal context collided with its title and fullscreen sat beneath the bottom navigation;
  320-pixel composer intents clipped; and effective 720x450 rendering squeezed top actions into
  vertical letters.
- The approved correction is one full standalone UTF-8 HTML document at the existing task-owned
  artifact path, with a collapsed reviewer harness separate from the product, one coherent
  master-detail/single-pane Web composition, a dedicated Project-or-Chat settings workspace,
  accessible per-capability policy groups, owned action hierarchies, one terminal, the exact
  9/67/118 Device catalog, honest QR evidence, seven shared composite scenarios and direct-load
  bootstrap. The production/test write set remains empty and P6-02+ remain frozen.

## P6-01 accepted replacement artifact and closure

**Completed:** 2026-09-03T07:37:12+03:00.

- The accepted task-owned artifact is
  `C:\Users\84vs1\.codex\visualizations\2026\09\02\01a06386-22d5-7833-bb82-40a4f499f52e\p6-01-neutral-coverage-ia.html`,
  exact SHA-256 `3217A5068BE741A20BC369FFC9B13B664C798C299A65A4BAFE07F1169E7B309D`,
  282,214 bytes. It is one standalone UTF-8 document below the 1 MiB budget with no external
  resource dependency. Direct load populated two initial messages, seven composite scenarios,
  all 76 coverage rows and the exact Device catalog of 9 destinations, 67 items and 118 pages.
- The retained responsive checks covered 1440x900, 1024x768, 720x450, 390x844 and 320x568. At and
  above 720 CSS px the artifact presents simultaneous master/detail; below 720 it presents one pane
  with an explicit Back owner. The final correction changed no geometry, typography or composition,
  and Architect confirmed the accepted visual/responsive result remained unchanged.
- The effective-capability proof uses one shared owner for display and submit. WebSearch and WebFetch
  require writable storage, a ready search service, a configured search key and a valid absolute
  HTTP(S) search URL. A malformed nonempty URL is rejected with retained unsaved input and prior
  committed state; an empty URL or removed search key makes both capabilities visibly unavailable.
  A required-Web send kept the message count at 2, retained its draft and Web intent, opened no
  pending authority and reported both unavailable capabilities. Restoring valid configuration or
  reloading returned the prior `Allow` baseline. Search-key removal updated `Not configured`, the
  top `Web · Off` summary and both detailed unavailable states simultaneously without navigation.
- The same-address reconnect scenario now calls the existing capture/restore owners. It moved from
  `field-notes/launch-checklist/Chat` to the alternate context and restored the exact project, chat,
  view and draft once with two messages still present, no pending approval or notice replay and
  focus returned to the prompt. The duplicate scenario restore path and synthetic Python outcome
  are absent. The three review-surface, two Project/Chat-scope and two Terminal/Files native buttons
  expose `aria-pressed`, unique accessible names and unchanged click plus Enter/Space behavior;
  `aria-selected` is absent from these non-tab controls.
- A fresh proof red-team reproduced the changed reconnect and accessibility boundaries and found the
  malformed-URL defect before closure. Its permitted blocker recheck confirmed the source correction
  but lost its browser environment, so it made no unobserved runtime claim. Architect personally
  reproduced the exact-final artifact, including URL/service availability, immediate key-removal
  rendering, required-Web forbidden effects, reconnect/no replay and segmented-control behavior,
  then issued explicit `ARCHITECT CLOSURE GO` for the exact hash above. That verdict also resolved
  the row-ordering gate: publish P6-01 first, activate P6-02 only after exact remote-SHA verification,
  and require P6-02's separate design/proof/write-set `GO` before any production edit.
- No firmware, production Web asset, generated header, schema, persisted value, route, test, build,
  upload, Device state or secret changed. The disposable browser viewport was reset, the exact-owned
  local artifact server was stopped and TCP port 65428 was verified free. The unrelated zero-byte
  root file `m[1])`, Architect-owned `.codex/agents` files and retained stash remain untouched.
  Residual risk is limited to this artifact being a reviewed design/proof rather than production;
  P6-02 and all later production work remain separately gated.

## P6-01 reopened acceptance correction

**Reopened:** 2026-09-03 after Architect's explicit ownership verdict. The user's visual STOP
invalidated the recorded P6-01 closure. The accepted-path artifact at SHA-256
`3217A5068BE741A20BC369FFC9B13B664C798C299A65A4BAFE07F1169E7B309D` has independently and
personally reproduced interaction, responsive-layout, action-hierarchy and preset-semantics
defects. P6-01 is again the sole `in_progress` row; P6-02 is pending and any locally retained P6-02
design package is historical prepared input only, not an active or approved implementation contract.

The correction is limited to the existing task-owned P6-01 artifact and this trace. It must:

1. make Project settings navigate to its owning workspace from Chat, Shared files, Terminal and
   Settings rather than unhide only Chat descendants;
2. replace the desktop in-flow Other chat actions expansion with a bounded anchored disclosure or
   overlay while retaining a usable mobile in-flow disclosure;
3. give 720x450 a compact/single-pane treatment where needed, collapse project/session utilities
   behind one clear disclosure, compact healthy status while leaving warnings/errors immediate,
   and keep the main title plus first useful action inside each retained initial viewport;
4. keep destructive API-profile, model-preset and optional-service key-removal actions local,
   content-sized and behind their selected-resource/service edit or danger disclosure, with
   STT/Search/TTS visibly grouped as services;
5. fit Allow once, Allow for chat and Deny inside every retained narrow viewport with pointer and
   keyboard reachability and no horizontal scrolling;
6. add explicit Web and Device `Apply to active project` for the selected model preset. Apply copies
   only model and output tokens through the existing project-settings owner, selection/creation does
   not apply, failure preserves prior project values, and no preset reference is persisted. Update
   the coverage row and a scenario to prove both the effect and forbidden effects.

The correction preserves the graphite/warm/rust visual direction, Wi-Fi discovered/hidden paths,
separate Terminal/Files and SSH/SFTP disclosure, terminal fullscreen/resize, grouped Shared/project
settings actions, nine icon-led Device destinations, every prior function/stable ID and the already
corrected Project capability-grid association. It adds no production asset, route, schema,
framework, design-system module, build or Device action.

Before another closure request, clean-load evidence must cover 1440x900, 1024x768, 720x450,
390x844 and 320x568; every product action/decision without overlap or clipping; title/first-action
reachability; Project settings from every non-Chat view; unchanged conversation header/work-canvas
geometry when opening Other chat actions; Web and Device preset Apply behavior and forbidden
effects; all seven composite scenarios; the complete 76-row and 9-destination/67-item/118-page
catalogs or explicitly corrected counts; zero console errors; exact artifact hash/size; and fresh
independent visual and functional red-team verdicts. P6-01 may not be marked completed, staged or
committed and P6-02 may not resume before a new explicit Architect closure `GO`.

## P6-01 reopened correction evidence-ready checkpoint

**Evidence-ready:** 2026-09-03T09:37:04+03:00. P6-01 remains the sole `in_progress` row and
P6-02 remains pending while this exact checkpoint awaits Architect's personal closure verdict.

- The corrected task-owned artifact is
  `C:\Users\84vs1\.codex\visualizations\2026\09\02\01a06386-22d5-7833-bb82-40a4f499f52e\p6-01-neutral-coverage-ia.html`,
  exact SHA-256 `DA69622052F935FB5033E2A0EE7631FE56F71F3D8C68F995B9370FEBA50C1714`,
  291,978 bytes. It remains below the 1 MiB budget and contains no external script, Fetch, XHR,
  WebSocket or project-to-preset reference. Script parsing passed, all 355 IDs are unique, and every
  queried correction control exists.
- Clean direct loads at 1440x900, 1024x768, 720x450, 390x844 and 320x568 had document scroll width
  equal to client width, no horizontally overflowing visible control and no console warning or
  error. The compact initial views retained the main title and first useful action above the fixed
  navigation. At 1024 and below one Console-actions disclosure owns project/session utilities, one
  compact healthy summary replaces healthy detail, and a forced provider warning remained
  immediately visible as both the aggregate warning and detailed provider failure.
- Project settings navigated to the owning settings workspace from Chat, Shared files, Terminal and
  Settings at both 1440 and 1024 widths. Each Back action restored the exact source view and focus to
  the Project-settings opener. Opening Other chat actions at 1440 left the conversation header at
  `[444,184.35,980.8,154]` and work canvas at `[444,338.35,980.8,296.85]`; at 1024 their heights and
  boundary remained 147 and 331.35 CSS pixels. The menu stayed inside the viewport at both desktop
  widths and became an in-flow eight-action disclosure without overflow at 720, 390 and 320.
- API-profile and model-preset deletion were absent from the closed state and appeared only as
  local content-sized actions inside their selected-resource danger disclosures. STT, Search and
  TTS rendered as three distinct service groups, and each key-removal action was absent until its
  own local danger disclosure opened. At 390 every opened action remained inside its settings pane.
- At 390 the pending-decision dialog/content measured 338/298 CSS pixels in both client and scroll
  width; at 320 they measured 268/228. Allow once, Allow for chat and Deny were fully visible,
  stacked at both widths, and keyboard order was exactly once, chat, deny without duplicate or
  hidden stops.
- Web preset selection and creation left the active project's model and output tokens unchanged.
  Applying `Fast` copied only `gpt-5-mini` and `1024`; no preset reference was stored. A forced
  settings/storage failure preserved the exact prior project values. The Device representative
  flow separately reproduced select-only, explicit apply confirmation, successful two-field copy,
  no-reference result and failure preservation; reselection remained inert.
- Direct-load coverage remained exactly 76/76 rows. The exhaustive Device catalog remained nine
  destinations, 67 items and 118 pages with per-destination page totals
  `16,19,6,6,19,12,17,19,4`. Baseline, authority, storage, remote, session, settings and Device
  composite scenarios each completed a full cycle in its owning surface with zero console errors.
- A fresh functional proof red-team reproduced every correction, count, Web/Device preset success
  and forbidden effect, all seven scenario cycles and the empty console, then returned `GO` on the
  exact hash and size above. A separately dispatched fresh visual red-team returned `GO` on the same
  bytes after independently checking all five required viewports, responsive reachability and
  clearance, Project-settings routing, anchored-menu geometry, danger hierarchy, service grouping,
  pending-decision fit/order and the graphite/warm/rust visual hierarchy.
- No firmware, production Web asset, generated header, schema, persistence, route, test, build,
  upload, Device state or secret changed. The disposable browser viewport was reset, the
  exact-owned artifact tab and server were closed, and TCP port 65429 was verified free. The
  unrelated root file `m[1])`, `.codex/` state and retained stash remain untouched. Residual risk is
  limited to this being a reviewed interaction/design proof rather than production behavior; P6-02
  and every production boundary remain separately gated.

## P6-01 reopened correction closure

**Completed:** 2026-09-03T09:40:13+03:00.

- Architect personally reconciled the exact six-clause correction contract, row-owned artifact and
  trace diff, every affected producer/consumer, native browser semantics, all retained proof,
  cleanup, resource budget and residual risk. Architect issued explicit `ARCHITECT CLOSURE GO` for
  exact artifact SHA-256 `DA69622052F935FB5033E2A0EE7631FE56F71F3D8C68F995B9370FEBA50C1714`,
  291,978 bytes, after the fresh functional and visual red-team verdicts both returned `GO` on those
  same bytes.
- The publication boundary contains only the P6-01 reopened contract, evidence and closure record.
  The locally retained P6-02 activation/pre-edit package is not P6-01-owned and must remain unstaged
  until this correction commit is pushed and its exact remote SHA is verified. P6-02 remains pending and no
  production work is authorized during this zero-active-row publication window.

## P6-01 second acceptance revocation and canonical re-audit

**Reopened:** 2026-09-03T20:43:17+03:00 after the user's exact STOP and Architect's ownership
verdict. The prior correction commit
`1b0d49039697c7abe5014e3d2841b632639706a8` is remotely published and independently verified, but
its artifact acceptance is revoked. P6-01 is again the sole `in_progress` row; P6-02 and every
production, route, schema, persistence, build, upload, Device and Web test boundary remain frozen.

- The user reports missing functions and rejects the composition and functional information
  architecture as a whole. The concrete observations include a context-blind `Load more` control
  without a clear target, count, direction or state; a developer-facing Terminal strip that gives
  `Geometry 120x32`, `Clear`, `Fullscreen` and `Connect` flat, incorrect priority; visually touching
  adjacent bordered objects; inconsistent spacing/alignment; and no clear discoverable chat action
  or message-mode selector. The user's rhetorical rejection is not a request to explain those
  controls and cannot be reduced to two label fixes.
- The artifact's own 76/76 table, catalog counts and prior no-overflow geometry are no longer
  authoritative acceptance evidence. Those checks did not prove spacing rhythm, separation between
  adjacent boundaries, a coherent alignment grid, task hierarchy, discoverability or semantic
  reachability. Prior functional and visual GO verdicts are retained only as historical evidence.
- Before any artifact correction, reconstruct a fresh canonical inventory from `ROADMAP.md`, the
  final P3/P4/P5 traces and the actual shipped Web and Device producers/consumers. Compare every
  real user action, legal state, explicit failure/degraded path and cleanup/recovery path against the
  artifact independently of its self-authored coverage table.
- The audit must trace the shipped per-message contract — Auto, No tools, exact Web, Files, SSH and
  Python intent plus applicable Safe Actions/tool selection — into an explicit usable chat control.
  A collapsed generic `Message options` disclosure does not establish discoverability. Inspect
  every adjacency/contact across collections, selected-object surfaces, action bars, Terminal,
  Files, Settings and compact/mobile layouts.
- The only permitted output before review is one consolidated omission/usability report and the
  smallest coherent correction design preserving all shipped functions. Do not patch isolated
  screenshots or incrementally salvage the current composition. The task-owned artifact remains
  frozen until Architect independently reviews the complete inventory and redesign contract.
- Task-clock hypothesis: the rejected artifact counted named destinations and simulated scenarios
  without deriving action meaning, legal ownership or composition from the final production
  surfaces. Source/trace inventory is expected to identify omitted or mis-prioritized actions and a
  smaller user-task hierarchy. No experiment has been repeated and no production state is touched.

## P6-01 canonical source re-audit and replacement pre-edit package

**Frozen:** 2026-09-03T21:12:55+03:00, awaiting Architect review before any artifact edit. The
rejected artifact remains byte-identical at SHA-256
`DA69622052F935FB5033E2A0EE7631FE56F71F3D8C68F995B9370FEBA50C1714`. The complete final
`ROADMAP.md`, P3, P4 and P5 traces, active P6 trace, shipped Web asset/routes/state owners and shipped
Device menus/input/render owners were read independently of the artifact's catalog. The prior
literal `76`, `9/67/118`, no-overflow and visual/functional GO claims are historical only.

The audit uses three explicit classifications:

- **Shipped** means a current production producer and reachable consumer exist. Static or retained
  trace evidence is not promoted to a fresh physical Device or live SSH/Python observation.
- **P6 parity gap** means the active phase authorizes a missing required interface or state, but the
  replacement must not describe it as already shipped. The gap remains production work owned by its
  later P6 row.
- **Remove** means the rejected artifact invented an action, changed shipped semantics, leaked a
  reviewer control into the product, or exposed an implementation value as a user setting.

Coverage is checked in both directions from independent sources. `ROADMAP.md`, the final P3/P4/P5
traces and the actual shipped Device/Web producers and reachable consumers produce the matrix first;
every canonical action, required state/legal outcome and forbidden effect must then reach the
artifact. In reverse, every artifact control must map to one exact shipped owner or one explicit P6
gap. The check fails when a real source action is absent from both the matrix and the artifact; the
artifact and matrix cannot validate each other by sharing the same omission.

### Compact canonical coverage matrix

| Family | User goal and visible/reachable control | Required state variants and legal outcomes | Actual production owner and classification |
| --- | --- | --- | --- |
| Global Web shell/session | Authenticate; navigate Chat, Shared files, Terminal and Settings; keep active Project context visible; refresh the current owner; inspect health/pending state; Lock; End Web Console | Invalid password and five-attempt/30-second lockout; authenticated/expired; current shipped fixed 15-minute idle session; P6 choices 15 min/1 h/8 h/until reboot; distinct visible-tab identity, Browser connected, Waiting and auth state; same-address reconnect; SD/provider/Wi-Fi/Python/SSH status | Shipped shell and session owners: `assets/web_console.html:22-23,42,57-63,75,105-116,222-223`, `web_console.cpp:51-53,503-517,1395-1528`. Four lifetimes, presence/heartbeat and reconnect preservation are P6-03/P6-04 gaps. Refresh must never claim to rescan/restart a subsystem when it only reloads the current state view. |
| Projects | The sole active-Project switcher lives in the context bar and opens Project manager. Project manager owns named New project, Project bundle Import through the existing Shared-file/upload picker, Project bundle Export, and the bounded Project collection. Its selected-Project header owns Open chats, Settings and named More actions: rename, duplicate, Archive/Restore and delete; Settings owns instructions, real model override, context/output, auto-compact, SSH ceiling, eight policies and Shared links | Loading/empty/error/EOF/current/archived; exact selection survives page loads; invalid/colliding bundle never activates a partial import; write and degraded-SD errors; last Web Project deletion creates/selects `Default` and never deletes global Shared files. Import/Export remain Project-manager actions even when Import consumes the Shared picker | Web create/import/select/settings/actions are shipped: `assets/web_console.html:24,38,58-59,116-123`, `web_console.cpp:1660-1686,2651-2924,3412-3471`. The Web Project pagination route/JS exists but has no reachable DOM consumer because `loadMoreProjects` is absent, so Web Project pagination is an explicit P6-05 parity gap. Device create/import/select/settings/actions and Previous/Next pagination are shipped except Delete: `CardputerAssistant.ino:1057-1183`, `KeyboardNavigation.ino:84-525,2200-2225`. Device Delete is a P6-06 gap. Project API-profile assignment remains P6-02. |
| Chats/conversation | Chat owns only the bounded current/archive Chat collection, New chat, selected conversation and Chat export (`.md`). The selected conversation exposes title/model/context/W/F/S/P state, archived/raw history, messages/stream, summary/full-history/sources, Chat settings and named More actions: rename where owned, Pin/Unpin, Archive/Restore, duplicate, Export Markdown, compact, clear and delete; composer, Send, streaming Stop and contextual Retry | Loading/empty/error/EOF; archived-history cursor and count; active selection stable; pin forces unarchive and archive forces unpin; last deletion creates/selects `New chat`; retry reuses the accepted failed request's exact intent and one-turn instructions without duplicate user append. Web Retry may accept a new `maximum_output_tokens`; blank retains the failed request's value. Success resets volatile intent only after durable append | Web Chat pagination and actions are shipped reachable: `assets/web_console.html:24-25,38,80-89,116-134,210-220`, `web_console.cpp:1687-1748,1844-2242,2974-3693`. Device shipped: `CardputerAssistant.ino:1206-1388,1848-2172,2204-2388`, `KeyboardNavigation.ino:528-1404,2798-2867`. Project bundle Export is consolidated under Project manager rather than duplicated in Chat. Device Chat Rename is a P6-06 gap. Web search-source detail is a P6-05 gap; Device owns it under selected Chat, never AI. |
| Per-message permissions, Pending and Activity | Always-visible `Auto`, `No tools`, `Web`, `Files`, `SSH`, `Python` beside the prompt; one accessible capability/tool explanation; Project/Chat settings own persistent policies separately; Pending and Activity are reachable from Chat/status and Device AI | `Auto` and `No tools` are exclusive modes; any nonempty W/F/S/P subset is Required and cannot elevate policy; required denied/unavailable fails before provider; typed file diff, byte-exact SSH command, exact Safe Action, Python identity plus complete-source route, safe generic preview; Policy Ask allows once/chat/deny, mandatory removes allow-for-chat, stale/reboot exposes acknowledge/discard only; Activity shows tool, coarse target, state, duration, bytes and optional exit | Web shipped group-mask control: `assets/web_console.html:25,40,45-49,80-85,112-113,134,210-215`. Device shipped sheet/status: `src/ui.cpp:508-596`, `CardputerAssistant.ino:2204-2388,2491-2584`, `KeyboardNavigation.ino:823-833,998-1137`. Exact catalog: `src/tool_catalog.cpp:6-44`. There is no direct Safe Action route: the model chooses the exact schema after the user chooses a group. A visible explanation may name Logs, Service state, Containers, Disk and Processes but must not pretend to launch them. Complete Python source navigation is a P6 correction gap. |
| Shared workspace/files/QR | Shared Files owns New text file and Upload, never Project bundle Import. It owns the bounded file collection and selected-file header with Open/Save as the task primary; named More actions for Download, Save copy where owned, Rename, Link/Unlink and QR; isolated Delete; visible-section editor/navigation. Project Import may open this surface as a picker while Project manager remains the action owner | Text/bundle/binary explicit; uploaded safe text remains editable; nested safe paths, invalid/collision/stale-window/storage errors; one file may link to several Projects and rename/delete stays blocked until unlinked from every Project; QR rejects empty, invalid UTF-8 and over 320 bytes; full/read-only versus missing/removed/replaced SD effects remain distinct | Web Upload/open/window/save/download/rename/delete/QR are shipped: `assets/web_console.html:26,58,95-98,193-209`, `web_console.cpp:2927-2972,4660-5045`, `file_workspace.cpp:1240-1248,1283-1289`. Web New text file, Save copy, Files pagination and Link/Unlink are explicit P6-05 gaps: their routes/JS may exist, but shipped DOM lacks `loadMoreFiles`, `toggleProjectLink` and `projectLinkState`, so there is no reachable consumer. Device New text, paging and Link/Unlink are shipped: `DeviceMenus.ino:217-274`, `KeyboardNavigation.ino:2164-2693`. Device has no Download, copy-selected-text or QR-selected-file control; do not invent them. |
| SSH profiles/security/terminal/SFTP | Profile collection and separate selected-profile editor; New/select default/edit/delete/key install; profile/endpoint/trust/status context above exactly one terminal; state-owned Connect/Disconnect primary; exact trust/mismatch/Forget; direct desktop typing and narrow touch input; subordinate terminal tools; separate Remote files task with exact source/destination, overwrite confirmation and Cancel | At most five/incomplete/capacity; secrets and passphrase write-only; profile locked during connect/trust/terminal/mismatch; disconnected/connecting/trust/auth/open/connected/stopping/failed/mismatch; timeout/nonzero/cancel/partial/SD-log download belong to model command outcomes; SFTP known failure versus outcome unknown and no retry; changed-key Forget never reconnects | Web shipped: `assets/web_console.html:27,94,141-192,221`, `web_console.cpp:3836-4658`. Device shipped: `SshTools.ino:3-99,1356-2040`. PTY auto-fit is `ResizeObserver -> /api/ssh/resize`, 20..240 columns and 4..100 rows; it is not a manual Geometry setting. Clear resets only the browser buffer; Fullscreen targets terminal output. Manual Terminal and model SSH/Safe Action/SFTP authority remain distinct. Remove fake geometry, terminal-session tabs, fabricated exit 0, Complete transfer and synthetic `../` claims. |
| Settings/providers/device controls | Category list to one detail form: Session/security; Wi-Fi; AI/API profiles/model presets; Tool access; Voice/Search; Device; Browser; Python; Diagnostics; Activity. Persistent global settings retain one truthful commit owner; each profile/preset object has one save owner. Browser-local Surface style, Compact density, Reduce motion and Keep terminal awake remain functional controls and apply immediately; Diagnostics separately owns a session-only metrics enable/disable action | Wi-Fi explicit scan/refresh, discovered 2.4 GHz choice, separate hidden/manual path, empty/error/connecting/connected/failure and write-only password; model discovery populates the real model field; API profile/preset limit remains `bounded; measured in P6-02`; STT/Search/TTS stay independent; device apply can fail; all four browser preferences visibly apply and keep-awake is effective only while terminal is connected and visible; diagnostics toggle/loading/error are actionable while metric values and Activity rows are read-only | Shipped Web settings and browser preferences: `assets/web_console.html:28-36,90,135-140,221`, `web_console.cpp:3530-3833`. Current persistent owner is one `Save all settings`; categories cannot invent separate commits. `diagnostic_metrics` is a real session-only action backed by `assets/web_console.html:34,65,78,105,140` and `src/web_console_routes.cpp:157`; the replacement moves it out of Browser preferences into Diagnostics without removing it. P6-02 owns profile/preset persistence/counts, P6-03 lifetime, P6-05 Wi-Fi scan/backend mapping. Device uses immediate per-item persistence in `DeviceMenus.ino:75-130`, `KeyboardNavigation.ino:2032-2138`, not Web save semantics. Only reviewer presence controls such as `Simulate last tab`/`Send visible heartbeat` stay outside product UI. |
| Python | The manual MicroPython workspace owns script list, New, Open, Save file, Run, Refresh output, Restart Python and Return to CardMind. Separately, Chat owns Python intent and the P5 one-shot Pending/full-source approval, handoff to one foreground run, same-address Web or Device return and attachment to the originating Chat | Manual workspace: no selection/new unsaved/loaded/saved/running/output/error/restart/return. One-shot: invalid/unlinked/too-large/non-UTF-8 source; exact path/size/SHA and privileged/no-sandbox warning; Allow once/Deny only; cancel before staging; handoff/running; success/exception/normal reset/watchdog or power-loss effects unknown; already attached/no replay; artifact present/absent/access error | Manual shipped workspace: `micropython/vfs/cardmind_supervisor.py:533-617,742-803`. P5 one-shot owners plus `assets/web_console.html:33,90,137,210-215` and Device Web Console/Pending owners remain separate. Current Web Pending modal has no complete-source route; current Device prefix is bounded and full review requires Files. Startup currently lands on Main Carousel, not proven originating Chat. Full-source return and Device origin restoration are P6 correction gaps. The artifact presents both surfaces and states but never simulates Python execution or implements either state machine. |
| Diagnostics/degraded/cleanup | Compact global status opens Diagnostics. Diagnostics owns the real session-only Enable/Disable performance metrics action; the resulting metric values and all Activity rows are read-only. Explicit Retry belongs to the failed read owner; applicable replacement confirmation is visible; exports remain secret-free | Metrics enabled/disabled, update/loading/error; SD ready/full/missing/removed/replaced are shipped Web states; corrupt/read-only are required design/review states only where the authoritative owner supports them; provider/model, optional STT/Search/TTS, Wi-Fi, session, SSH, Python and diagnostics failures stay distinct; success/failure/partial/effects-unknown and observed cleanup never collapse to Ready | Web diagnostics toggle/metrics/activity/export: `assets/web_console.html:34-36,65,77-79,105,110,138-140,221`, `src/web_console_routes.cpp:157`, `src/web_console_state.cpp:100`. Device Diagnostics remains two read-only pages with no export: `FileTools.ino:70-105`, `KeyboardNavigation.ino:2695-2708`. Diagnostics as a Web surface is therefore not wholly read-only. Reviewer scenario/presence selectors stay outside the product and cannot be counted as actions. |
| Device 240x135 | Nine ordered destinations and all real nested screens remain visually inspectable; Home uses one selected icon/label with neighbour names and index; each list/task screen shows its real key footer; Chat exposes current message intent plus both the direct and non-shortcut capabilities paths | Shipped Home uses Left/Right/Enter and consumes Esc as an explicit no-op; current left/right transition is animated. Ordinary lists clamp Up/Down and Esc returns parent; synchronous SSH modal lists may wrap; G0 and Fn+8 are Chat-only; fatal boot screens are blocking; degraded SD is not fatal. The replacement's reviewed direction is a static carousel, and every P6-only screen is labelled as a gap | Shipped enum/dispatcher: `CardputerAssistant.ino:86-138,1418-1592`; animated Home: `DeviceMenus.ino:276-329`; keys and Esc no-op: `KeyboardNavigation.ino:52-82,1448-1480`; fatal: `CardputerAssistant.ino:3366-3426`, `src/ui.cpp:345-358`. Quick notes/Checklist enter the generic file editor; Help is one Controls viewer; there are no specialized checklist CRUD, About/Support, global G0/Fn+8, recoverable fatal screen or hidden-SSID Device picker. |

### Consolidated rejection findings

1. The artifact demotes the defining Chat action behind generic `Message options`, while production
   exposes the six intent controls at composer level. It also lists Safe Actions only in coverage
   prose. Exact Safe Action execution cannot be added as a fake button because no direct route or
   exact-tool intent exists.
2. `Load more`/`Load archived` does not represent production pagination. The reachable Chat `More`
   fetches the next mixed physical JSONL page (maximum 32) in stored order. Project and Files route/JS
   logic can fetch their next bounded page, but the shipped DOM has no reachable consumer; those
   artifact controls must be explicit P6 gaps. Archived messages load from the raw-history byte
   cursor in bounded chronological batches. Every footer needs target, direction, loaded count,
   loading/error and EOF; it must not invent a remaining total when the server does not provide one.
3. Project/Chat actions are duplicated or false: two Delete aliases share one handler, `Save
   instructions` aliases a larger save owner, inverse actions are not state-labelled, last-object
   deletion is incorrectly blocked, and Pin/Archive coupling is absent.
4. The Terminal gives automatic geometry, browser-local Clear, output-only Fullscreen and Connect
   equal priority, mixes profile editing/SFTP/terminal in one wall and fabricates successful command
   output. At compact sizes controls and selected-file actions are occluded by navigation.
5. Files mixes its collection creation, Project Import, selection actions, editor navigation and QR;
   selected actions are buried. Project Import is misowned, linked-file rename/delete safety is not
   legible, and route-only Web Link/Unlink and Files paging are presented as shipped controls.
6. Settings leaks reviewer actions into product UI, saves Surface style/Compact density without
   applying them, detaches discovered models from the actual model field and conflates independent
   optional-service states. It also treats all Diagnostics as passive telemetry, losing the real
   session-only performance-metrics toggle even though metric values and Activity rows are read-only.
7. The Device simulator changes Home/list key semantics, globalizes Chat-only G0/Fn+8, invents a
   recoverable fatal screen and multiple actions, misowns search sources and Python results, and
   counts static storyboard text as behavior. Several retained P4/P5 Device claims are static rather
   than fresh physical UI evidence and must remain labelled honestly.
8. The artifact is a large parallel mini-application whose circular self-authored inventory and
   geometry checks did not test task hierarchy, boundary separation, action meaning or production
   ownership. It is not a base for incremental repair.

### One replacement information architecture: context rail plus task canvas

The replacement uses one rule across the Web surface: the shell owns navigation/session/current
context; each destination owns only its named collection actions and pagination; the task canvas
owns the selected object; the selected-object header owns one primary action and at most one
frequent secondary; a named `More actions` menu owns the rest; destructive actions appear once in a
separated danger group. Cross-surface pickers may supply a value without taking ownership of the
invoking action.

| Region | Content and ownership |
| --- | --- |
| Global rail | Chat, Shared files, Terminal, Settings. Active state has icon plus text and does not rely on color. |
| Context bar | The sole active-Project switcher, current page/object title, one compact health/pending entry, and a named Session menu containing Lock and End Web Console. The switcher opens Project manager; no second Project switcher appears in Chat. |
| Project manager | New Project, Project bundle Import and Project bundle Export; current/archive Project collection; selected Project settings/actions. Import invokes the existing Shared-file/upload picker, then returns to the same Project-owned validate/import/activate flow. |
| Chat collection rail | New chat, current/archive view of the mixed loaded Chat records, selected Chat and the shipped target-specific Chat footer. Chat owns only Export Markdown; it never duplicates Project bundle Export. On narrow layouts this is a separate screen. |
| Chat task canvas | Conversation header, model/context/effective capability text, Chat settings & actions, internally scrolling transcript, contextual archived-history control, contextual retry, and a composer that remains visible. |
| Files collection rail | New text file and Upload; bounded Shared list/breadcrumb, type/link state and collection footer. It can serve as the picker opened by Project Import but never owns an Import action. Web Files paging and Link/Unlink are visibly labelled P6 gaps until P6-05 supplies reachable consumers. |
| File task canvas | Selected-file identity/type/link summary; Open or Save primary; named More for Download/Save copy/Rename/Link/QR as actually owned; separated Delete; bounded editor section and navigation. |
| Terminal context | Selected public profile/endpoint/trust/state. `Connect` or `Disconnect` is the sole connection primary; retained mismatch substitutes exact Forget. Profile management is a separate list-detail screen. |
| Terminal task canvas | Exactly one auto-fit PTY with direct desktop input; narrow touch input only where required. `Clear screen` and `Fullscreen terminal` are subordinate terminal tools. SFTP/Remote files is a separate subordinate task within the same single connection, not another terminal/session tab. |
| Settings | Category list plus one single-column detail form. Natural pairs such as Host+Port may share a row. Persistent global settings expose one truthful dirty/save owner; profile/preset objects each expose one. Surface style, Compact density, Reduce motion and Keep terminal awake are functional browser-local controls and visibly apply immediately. Diagnostics separately owns the session-only performance-metrics toggle; metric values and Activity rows, not the whole Diagnostics surface, are read-only. |
| Python workspace | A distinct manual surface owns script list, New, Open, Save file, Run, Refresh output, Restart Python and Return to CardMind. Chat Pending separately owns the P5 one-shot full-source approval/handoff/attachment flow; neither surface pretends to execute Python in the artifact. |
| Review rail | Clearly outside the product frame. It selects SD, session, pagination, Pending, SSH, Python and connector states for visual inspection only. Presence/heartbeat scenarios live here, not in product Settings. It contains no product action and makes no backend/timer/persistence claim. |

Chat message intent is not a generic disclosure. A labelled `Tools for this message` strip remains
visible immediately above the prompt at every width. `Auto` and `No tools` are exclusive; toggling
one or more of Web/Files/SSH/Python enters the Required subset. Each selection includes a visible
check/text state, not color alone. Output limit remains compact and one-turn instructions remain
reachable without covering the intent strip. With SSH eligible, an adjacent `Available SSH tools`
explanation names arbitrary Command, SFTP list/read/write/move and the five fixed Safe Actions and
states that CardMind chooses the exact allowed tool. Pending and Activity then show the exact tool.
No direct Safe Action launcher or promised exact dispatch is added.

### Action, state and pagination rules

- Project manager alone owns New Project, Project bundle Import and Project bundle Export. Import
  opens Shared Files/upload as a picker without transferring action ownership. Chat owns New chat
  and Export Markdown only. Shared Files owns New text file and Upload only. A selected object never
  repeats these collection controls.
- Send becomes Stop only during streaming. Retry is attached to the failed request and displays the
  retained intent and one-turn instruction snapshot it will reuse. Web Retry may accept a new
  maximum-output value; leaving it blank uses the retained failed-request value.
- Connect becomes Disconnect only when that lifecycle owns the terminal. Trust and mismatch replace,
  rather than join, ordinary connection actions.
- Labels are current-state verbs: Pin or Unpin, Archive or Restore, Link or Unlink. Destructive
  actions are never duplicated or visually equal to the task primary.
- Web collection footers use truthful available data: `Projects · 32 shown · Load next page`,
  `Chats · 32 shown · Load next page`, `Shared files · 64 shown · Load next page`; loading disables
  repeat, error changes the same control to `Retry loading …`, and EOF reads `All loaded … shown`.
  The Chat footer is shipped; the Project and Shared-files footers carry an explicit `P6 gap` label
  until P6-05 adds their missing reachable DOM consumers.
  A remaining count appears only for archived messages where production supplies it, for example
  `Archived history · 8 loaded · Load next 8 · 20 remaining`. Device keeps its shipped target and
  direction labels such as `< Previous projects` and `Next projects >`.
- File windows say Previous/Next section and show byte/section position as secondary state. They do
  not expose an implementation `chunk` as a user object.
- Empty, loading, validation error, connector failure, cancellation, timeout, partial success and
  outcome unknown are rendered beside their owning object/action, not only in a five-second global
  toast.
- Project import visibly selects a bundle, validates, imports and activates. Python approval visibly
  opens the exact complete source and returns to the same Pending identity before Allow once can be
  chosen. These are UI routes, not simulated backend execution.

### Responsive scroll and focus model

- The shell is a `100dvh` grid. Global navigation, context bar and mobile navigation occupy grid
  tracks, never fixed overlays. The work track is `minmax(0,1fr)`.
- At 1280x720, the global rail, 280-320 px collection rail and flexible task canvas coexist. At
  900x720, the global rail becomes icon-led and the object inspector is an explicit sheet. At
  720x450, secondary actions move into named More menus while Chat composer and Terminal input retain
  their own visible bottom track.
- At 390x780/844 and 320x568, collection and selected object are separate routes with a labelled
  Back action. The four primary destinations occupy a non-overlay bottom grid track. The Chat intent
  controls use a two-row grid; the transcript scrolls independently above the persistent composer.
  Terminal output similarly owns the remaining scrollable height above its touch input.
- Independent bordered siblings have 16 px separation on desktop, 12 px on tablet and 8 px on
  phone. They never share/touch an edge. Only one intentional segmented control may share an outer
  boundary. The design uses one 4/8/12/16 spacing rhythm and one border language.
- Opening a selected object moves focus to its heading. Back restores focus to the exact list row.
  Sheets/dialogs trap focus, Escape closes, and close restores the invoker. Visible focus, selection,
  warning and destructive meaning never depend on color. At 200% text, inner task regions scroll;
  primary actions do not clip or become peer-button walls.

### Device navigation decision

Current production is an icon-led nine-destination carousel whose Left/Right transition calls
`animateCarousel`; it consumes Esc on Home as a no-op. Architect selected a deliberately static
replacement direction, not a grid and not a claim about shipped animation. Preserve exactly nine
ordered destinations, one large unique procedural icon, the full selected label/status,
previous/next neighbour names, `n/9`, and a high-contrast non-color-only focus marker. Product
interaction preserves Left/Right/Enter plus explicit Esc no-op; the replacement adds no animation,
extra framebuffer, widget system or theme. Every real destination/item/page must be visually
inspectable through an external reviewer screen selector, while representative product interaction
follows the real key owners. Static catalog prose remains mapping evidence, never behavioral proof.
P6-only parity screens are visibly tagged.

### Frozen artifact-only write set and resource/non-goals

After Architect GO, replace the contents of exactly
`C:\Users\84vs1\.codex\visualizations\2026\09\02\01a06386-22d5-7833-bb82-40a4f499f52e\p6-01-neutral-coverage-ia.html`.
No production asset, generated header, route, state, schema, repository test, build, upload, Device
state, extra artifact, external dependency or local server belongs to this correction. Existing
production semantic IDs are reused where the action exists; exact P6 additions and reviewer-only
controls receive explicit one-to-one mappings and cannot masquerade as shipped IDs.

The replacement is one lightweight self-contained HTML/CSS/JS visual prototype. It holds only
bounded sample records and presentation state needed to inspect routes/states; it does not simulate
NVS, cursor storage, SSH, SFTP, Python execution, timers, heartbeats or cleanup. It embeds no
self-authored pass counter, backend clone, arbitrary API-profile/preset capacity, default-deletion
policy, user-defined Safe Action framework, PWA, terminal tabs, reconnect scheduler, Share center,
Python jobs/package manager or future USB work.

**Binding visual clarification received from Architect on 2026-09-03:** retain the corrected IA and
all interaction/geometry owners, and develop the prior warm-light identity into a restrained USSR
laboratory/measuring-instrument treatment. Use warm enamel/ivory work surfaces, graphite instrument
and terminal wells, dark ink, muted oxide/rust primary, restrained signal green/teal for selected or
healthy state, amber warning and red danger. Panels are crisp square/soft-radius with calibrated
4/8/12/16 spacing, compact technical labels and mechanical-looking but accessible controls. This is
a token/component correction, not another structural rewrite or theme framework. No all-dark
cyber-terminal styling, propaganda/military styling, faux aging/noise, decorative screws, gratuitous
gauges/LEDs, Cyrillic gimmicks, gradients/glow/glass/pill soup, oversized empty cards, decorative
dashboards or monospace body copy. Preserve recognizable identity except for the smallest contrast
or semantic correction; check contrast and warning/danger distinctions before freezing the hash.

### Small requirement-derived proof matrix

| Proof | Required observation |
| --- | --- |
| Source mapping | An inventory generated independently from `ROADMAP.md`, final P3/P4/P5 traces and actual shipped Device/Web producers plus reachable consumers maps source -> matrix -> artifact for every user action, required state/legal outcome and forbidden effect. Reverse traversal maps every artifact control to one exact shipped owner or explicit P6 gap. The check fails when source behavior is absent from both matrix and artifact; removed/diagnostic/static-only items never appear as shipped, and old literal counts are absent as acceptance. |
| Reachability/ownership | One deterministic traversal starts from each meaningful noun and covers every product action, secondary control, named More disclosure, collection footer, sheet/dialog decision and reviewer route. Every included control opens its screen or changes presentation state, is in-view and operable; no inert control or catalog sentence counts. The context bar, Project manager, Chat, Shared Files, selected object, task and danger actions each have exactly one owner. |
| Composer/Pending/Activity | Six message-intent choices, W/F/S/P unions, selected text/check state, denied/unavailable error, durable-send Auto reset and Retry's fixed intent/instructions plus optional Web maximum-output override are inspectable. File diff, exact SSH/Safe Action, complete Python source, stale/reboot acknowledge and every Activity field have reachable variants. The separate manual Python workspace exposes script list/New/Open/Save/Run/Refresh/Restart/Return without simulating execution. No fake exact-tool launcher exists. |
| Collection semantics | Shipped Chat paging and explicitly P6-labelled Web Project/Files paging scenarios demonstrate target, direction, loaded count, disabled loading, advancing cursor/page, EOF, empty, error/retry and preserved selection; history adds its real bounded cursor/remaining semantics. Project Import/Export stay in Project manager, Chat exports Markdown only, and Shared Files owns New text/Upload only. Last Project/Chat deletion and Pin/Archive coupling match production. |
| Files/terminal/settings | Uploaded text remains editable; bundle/binary/link restrictions, explicitly labelled Web Link/Unlink gap and QR bounds are visible. Terminal preserves direct typing, auto-fit, lifecycle priority, profile locking and error/partial/log/SFTP states. Models populate the actual field; optional providers stay independent. Surface style, Compact density, Reduce motion and connected-visible Keep awake visibly apply; the session-only Diagnostics metrics toggle is operable while metric values and Activity rows remain read-only. |
| Responsive geometry | The exact same reachability traversal runs without omissions at 1280x720, 900x720, 720x450, 390x780, 390x844, 320x568 and 200% text. Automated bounds plus screenshots show no horizontal overflow, border contact, clipped focus/action/footer/dialog or nav occlusion; Chat composer and Terminal input remain visible. A fresh human visual review checks hierarchy, alignment, the 4/8/12/16 spacing rhythm, typography, palette and absence of prohibited synthetic motifs including gradients, glass, glow, pill soup, oversized empty cards and decorative dashboards. |
| Keyboard/focus/Device | Web native tab order, focus return and Escape behavior pass at every frozen viewport and 200% text. Device Home shows the proposed static presentation while preserving the shipped nine-item order, neighbour labels, `n/9`, non-color focus, Left/Right/Enter and explicit Esc no-op; ordinary lists clamp, Chat-only G0/Fn+8 and every nested screen/state are inspectable; fatal remains blocking. No claim says the shipped carousel is static. |
| Product/reviewer isolation | Reviewer state/presence selectors remain outside the product frame, never change product action inventory and make no runtime/persistence claim. Static and runtime checks prove one self-contained artifact with no external assets or backend/timer/storage clone, exact SHA-256 and size below the retained 1 MiB ceiling, and zero page/console errors. No secret/internal ID, invented readiness, unsupported cleanup or exact-once external-effect claim appears. |

P6-02 through P6-08 remain pending. The previously reviewed P6-02 package stays inactive and
unstaged; it is not authorization to edit production while this reopened P6-01 gate is unresolved.

### Artifact implementation clock checkpoint

At `2026-09-03T22:09:26+03:00`, the replacement artifact's observed creation time is
`2026-09-03T21:49:08+03:00`; the entire elapsed replacement/correction interval is therefore
20 minutes 18 seconds, an upper bound on primary active time because it includes bounded tool
waits. The longer open task turn also includes the mandatory pre-edit STOP/re-review wait and is
not one uninterrupted geometry hypothesis. No 60-active-minute threshold has been reached.

The last material approach change replaced per-container minimum-height/subtraction fixes with one
outer viewport grid: reviewer row, `minmax(0,1fr)` product track and status row; the product fills
that track, and the Web shell explicitly constrains its row. Dialog and fullscreen-terminal fixes
use their existing shared inner grid owners. The exact edit timestamp was not independently
retained, so the stall clock is conservatively still anchored at `21:49:08`, not reset by this
description. The current hypothesis is competing intrinsic grid/minimum sizes, not missing
breakpoints. The next proof is the unchanged all-control viewport traversal plus long-dialog and
normal/fullscreen terminal bounds; no production or new test family is authorized.

Checkpoint artifact SHA-256 is
`A9B8D71A968024D9302E6B7944250A9E1B9850CD8CA03CAA26BB2AEBF3922AA6`, 107,114 bytes.
This is an implementation checkpoint, not evidence-ready or closure acceptance.

### Replacement candidate: observed proof and unresolved gate

The interrupted candidate was verified unchanged at `2026-09-03T22:51:17+03:00`:
SHA-256 `62FF2A4D5CA16B31073BE0E8D6940E0E86A148BF4B70E11E14ADFF1070BB3FFF`,
131,296 bytes. A focused 320 px Python Pending observation then found its complete SHA-256
forcing the dialog body from 284 px to 573 px horizontal scroll width. The correction changes only
the existing metric pair to shrinkable grid columns and wraps long values. The resulting frozen
candidate at `2026-09-03T22:55:45+03:00` is
`7AF36EF66780E5C6EAB8CEFA719A96CB10C5E49BC09329CA59BA5EB405EAF025`, 131,350 bytes.
No production asset, generated header, route, schema, repository test, build or Device state changed.

Observed evidence is limited to the following, not a complete acceptance claim:

- Source reconciliation corrected exact eight policies and separate Master/New-chat editors;
  mandatory file replacement approval; source-bound 160-byte Python sample and matching SHA;
  streaming Stop; Project selection/Archive labels; bounded direct terminal typing/paste;
  SFTP source/destination selection; Web-key temporary-upload cleanup wording; Settings model,
  range and voice fields; manual Python selection/New/confirmation routes. Subsequent exact-boundary
  changes exposed multi-link, QR invalid/oversize, SSH lifecycle, independent service/SD states,
  current-view Refresh and rejected-import fixtures. These statements describe mapped controls,
  not verified real-device behavior or a blanket all-control pass.
- The warm-light candidate's evaluated color pairs have contrast ratios: body ink/paper 13.30,
  muted/paper 6.40, muted/canvas 5.66, disabled text/background 4.91, primary rust text 6.91,
  selected teal text 7.32, teal/selection 6.09, amber/warning 6.01, red/danger 5.70, terminal text
  11.66; meaningful neutral border/paper 3.82 and border/canvas 3.37. This is token-pair evidence,
  not proof of every composited/focus state.
- The same Chat, long Project-settings dialog, normal terminal, fullscreen terminal and Escape
  traversal was observed at 1280x720, 900x720, 720x450, 390x780, 390x844 and 320x568. Document
  width/height stayed within the viewport; composer/input/dialog footer remained in view; the outer
  dialog had no second scroll owner. At 720x450 terminal output grew from 78.09 px to 168.72 px;
  at 320x568 it grew from 90.39 px to 217.11 px. Escape restored normal terminal at each size.
- On the final candidate, every externally selectable Web presentation state was then rendered
  separately at each of those six sizes. Document width and the dialog/task/transcript/terminal
  regions had no horizontal overflow and the captured console error/warning lists were empty.
  This checks state rendering, not every secondary action, field or keyboard path. An earlier
  overlong batch timed out and is excluded; only completed per-viewport results support this claim.
- The all-control check **failed** on selected SSH identity: at 1280x720, Reset -> Terminal ->
  `Lab server` -> `Manage selected profile` showed the correct task context
  `Lab server / engineer@192.0.2.20:22`, but `cmSshName`, `cmSshHost` and `cmSshUser` showed
  `Field gateway`, `192.0.2.10` and `operator`. The artifact's `renderDialog('ssh-profile')`
  hardcodes a different sample. Shipped selection/save ownership is
  `assets/web_console.html:141-144`; this is P6-01 artifact ownership, not a firmware defect.
  The frozen candidate is therefore not evidence-ready; no production or oracle change follows
  from this failed observation.
- The available native `ctrl+plus` key was rejected by the browser tool. The documented Playwright
  `Control+=` path left the actual 1280x720 viewport, device-pixel ratio and 14 px body / 20 px
  heading unchanged. A 200%-text result is **not verified**. No DOM/style injection or artifact
  test-only zoom mechanism was added.
- The fresh visual specialist could not receive inherited screenshot images and had no browser
  surface; documented hidden-tab creation also failed. It issued no visual verdict. Architect
  explicitly took ownership of the independent visual verdict and any no-artifact-change image
  delivery. No screenshot/export framework or second review artifact was created.

P6-01 remains the sole `in_progress` row; P6-02..P6-08 remain `pending`. There is no independent
visual GO, all-control/200%-text pass, completion mark, staging or commit for this candidate.

Exact-owned review cleanup was observed at `2026-09-03T23:04:03+03:00`: the primary's temporary
browser tab was closed and its viewport override reset. PID `51644` was revalidated against the
bundled Python executable, exact artifact directory and port `65432`, then stopped; port `65432`
had zero remaining listeners. Other browser tabs and Architect's server were untouched. No Device
fixture, API credential or Wi-Fi configuration was read or changed by these artifact checks.

## P6-01 consolidated closure STOP after system restart

**Recorded:** 2026-09-07T13:19:57+03:00 after Architect's fresh direct browser/source review of
frozen artifact SHA-256 `7AF36EF66780E5C6EAB8CEFA719A96CB10C5E49BC09329CA59BA5EB405EAF025`.
Before any resumed artifact edit, test or diagnostic, the app's visible plan was restored from this
matrix with P6-01 as the sole `in_progress` row and P6-02..P6-08 `pending`. Production, repository
tests and P6-02 remain frozen. The only permitted correction write set is this trace and the existing
task-owned P6-01 artifact; no new artifact, production route, persistence, framework, backend
simulation, build, upload or Device mutation is authorized.

Architect's consolidated STOP replaces the prior candidate's unresolved closure gate with one
coherent artifact correction contract:

1. Bind each selected object's identity to its editor and legal outcomes: the selected SSH profile
   populates its own fields; New/Edit/Make default/Delete remain distinct; Project rename never
   duplicates, Project delete selects a remaining record and creates `Default` only after deleting
   the last; Chat delete retains/selects another when present and Clear visibly empties the
   transcript; Shared-file rename removes the old identity; Previous/Next are disabled at their
   respective section boundaries; bounded API profiles and model presets expose reachable New and
   Delete controls.
2. Preserve one action owner: Chat settings has one save action for instructions and settings, and
   Wi-Fi has one state-dependent Scan/Refresh action rather than two controls sharing one handler.
3. Render loading, empty, error/retry and EOF at the owning Chat, Project or Shared-file collection;
   a later loading/error state replaces retained EOF/page presentation. Created and selected records
   expose truthful `aria-selected`, and narrow Back restores focus to the exact selected row.
4. Make representative required routes operable: Device F2 capabilities uses its real key/control;
   Device New Project and New Chat reach their creation flows; Device Project Import and Web
   uploaded-bundle Import both show select, validate, import and activate; an uploaded unvalidated
   bundle always retains a reachable validation step.
5. Treat lock, expiry and lockout as non-dismissible authentication gates; localize missing/full/
   removed/replaced SD effects to Shared Files actions; distinguish core-provider outage from
   optional Search. Label reconnect as a P6-04 gap, waiting/presence/lifetime as P6-03 gaps and every
   missing API-profile/model-preset field or control as a P6-02 gap. Project settings must either
   render its claimed linked-file inventory or make no such claim.
6. Reuse the locked phone route/Back model at 320x568 for manual Python list and editor so the panes
   cannot overlap. Give the selected Shared-file editor the remaining task track and compact its
   footer while retaining Previous, Next and position.
7. Preserve the warm enamel/rust/teal USSR-instrument palette, one-scroll dialogs and terminal
   geometry. Add no new design direction, framework, breakpoint family, backend simulation or
   explanatory source prose. A 200%-text result must use a legitimate browser/user scaling method
   with no DOM, style or artifact injection; otherwise it remains explicitly unverified.

The correction approach is one identity-bound presentation model plus one owner-local collection
state per bounded sample collection, reusing the existing routes, handlers and `<=640px` route/Back
breakpoint. Expected observations are: deterministic CRUD identities and forbidden effects; one
handler per named action; owner-local collection-state replacement; every required Web/Device route;
non-dismissible auth and local degraded-state ownership; labelled P6-02/P6-03/P6-04 gaps; no
320x568 pane collision; usable file-editor height; unchanged terminal/palette/dialog semantics; and
reverse mapping of every control to one shipped owner or explicit P6 gap. The same all-control,
focus-return, contrast and geometry traversal must run at 1280x720, 900x720, 720x450, 390x780,
390x844 and 320x568 on one frozen SHA. This section records the correction contract, not acceptance
evidence, completion, staging or commit authority.

## P6-01 frozen correction evidence and closure-review request

**Evidence frozen:** 2026-09-07T19:11:01+03:00. The existing task-owned artifact at
`C:\Users\84vs1\.codex\visualizations\2026\09\02\01a06386-22d5-7833-bb82-40a4f499f52e\p6-01-neutral-coverage-ia.html`
is SHA-256 `8D6DC3F262A174F197CEDA69CDE67823E432682259D02170FF1AF3EAA91087D0`,
176,482 bytes. No source change followed this freeze. The repository production/test boundary,
P6-02, build, upload and Device remained frozen.

Observed evidence on this exact SHA is:

- The fragment contains one parsing script, no document wrappers, no external-resource markup and
  no fetch/XHR/WebSocket/EventSource, storage, timer or `sendBeacon` path. Its raw ownerless controls
  are exactly the four presentation-review controls outside the product frame.
- A fresh source reviewer found that the immediately preceding candidate rendered an accepted SFTP
  path through `innerHTML` without escaping. The correction changes only the two SFTP dialog output
  sites: Download Source renders `esc(state.remotePath+'/'+state.remoteEntry)` and Upload Destination
  renders `esc(state.remotePath+'/…')`. With remote path
  `/<button data-owner="forged-control">forged</button><img src=x>`, both dialogs rendered the entire
  value literally and contained zero forged controls and zero
  `img`/`iframe`/`object`/`embed`/`script`/`link`/`video`/`audio`/`source` nodes. The normal `/var/log`
  route still rendered `/var/log/observations.txt` and `/var/log/…`; both dialogs had zero ownerless
  controls.
- Chat, Shared Files, Terminal and Settings were measured at 1280x720, 900x720, 720x450, 390x780,
  390x844 and 320x568: all 24 cases had zero root horizontal overflow, rendered-control overlap,
  ownerless product control or closed-menu exposure, and each retained a visible heading and first
  action. Wide and narrow screenshots preserved the accepted warm enamel/rust/teal hierarchy.
- The long Project-settings dialog was measured at all six sizes. It fit the viewport, retained a
  visible header and footer, and `cmDialogBody` was its sole scroll owner in every case. The normal
  and fullscreen Terminal route was also measured at all six sizes: fullscreen set
  `cm-terminal-full`, hid collection/header/input, enlarged output with zero horizontal overflow,
  and Escape restored the exact normal display state.
- At 320x568, Chat Back restored focus to the exact `field` Chat row, Shared Files Back restored
  focus to the exact `route.md` row, and Escape from Chat settings restored its exact opener. The
  unchanged evaluated text/background pairs range from 4.91:1 for disabled text through 13.30:1
  for primary text on paper.
- The exhaustive identity/CRUD, action-owner, collection-state, required Web/Device route,
  authentication, degraded-SD/provider, import, QR, long-file and narrow-Python observations were
  obtained on the immediately preceding candidate. The only subsequent source delta is the two
  escaped SFTP output expressions above; a fresh proof red-team independently reconciled that delta,
  the current source and the repeated same-SHA security/layout/dialog/terminal/focus observations
  against all seven consolidated STOP clauses.

The original source reviewer rechecked only its own blocker on the exact hash above and returned
`GO-to-request-Architect`. A different fresh proof red-team independently verified the exact hash and
size and returned `GO-to-request-Architect`; it confirmed that missing API-profile/model-preset
capacity remains a P6-02 gap and the only numeric five-item cap is inherited SSH-profile behavior.
Native 200% text remains explicitly **unverified** because the available browser surface exposes no
legitimate user/browser scaling method; no DOM, style or artifact injection was used. This is an
evidence-ready request for Architect review, not P6-01 completion, staging or commit authority.

Exact-owned review cleanup completed at `2026-09-07T19:14:04+03:00`: the temporary browser viewport
override was reset, the task-created preview tab was closed, and the exact bundled-Python preview
process serving port 60740 was stopped. Ports 60740 and 64901 then had zero listeners. No other
browser tab or process was changed; no Device fixture, API credential or Wi-Fi configuration was
read or changed.

## P6-01 user-directed instrument-style correction

**Recorded:** 2026-09-07T19:20:59+03:00. A new explicit user direction supersedes the closure request
for artifact SHA-256 `8D6DC3F262A174F197CEDA69CDE67823E432682259D02170FF1AF3EAA91087D0`.
That artifact remains a frozen functional/evidence baseline, not a closure candidate. Its source and
proof `GO-to-request-Architect` verdicts do not transfer to a later hash. P6-01 remains the sole
`in_progress` row; P6-02 through P6-08 remain `pending`, and no completion, staging, commit or
production authorization follows from the superseded request.

The binding correction is a functional interpretation of USSR measuring instruments, not museum
costume or generic generated-console styling:

- use warm painted-metal/ivory work surfaces, graphite or near-black instrument zones, restrained
  green/teal and amber indications, and red only for danger, error or deletion;
- strengthen a crisp instrument hierarchy with thin frames/sections, utilitarian typography,
  monospace only for data/terminal content, and tactile, unambiguous button, switch and indicator
  states;
- group actions by object and frequency: the primary action stays beside its object, secondary
  actions form one compact owner-local group, and rare or dangerous actions remain behind an
  explicit disclosure and confirmation;
- preserve every prior functional route and legal state: identity-bound CRUD, one owner per action,
  owner-local loading/empty/error/retry/EOF, truthful selection and focus return, authentication
  gates, degraded SD/provider states, Device/Web routes, imports, Terminal/fullscreen geometry,
  separate mobile Python routing and the usable Shared-file editor;
- show no hidden feature, inert or false product element, decorative meaningless scale, pervasive
  fake screw/marking, glow, gradient, effect shadow, card-for-card's-sake treatment or total
  monochrome. Keep monospace out of normal prose and navigation.

The correction stays inside the existing task-owned HTML/CSS/JS artifact and this trace. It adds no
framework, route, schema, asset, backend simulation, production file, test, build, upload or Device
mutation. Responsive proof must include 320 px, 640 px and desktop Web layouts and the separate
240x135 Device presentation model, with an explicit artifact-size/resource budget. Before the first
artifact edit, the primary must freeze the exact selector/markup write set, non-goals and smallest
functional/state/interaction/layout proof, then obtain one bounded independent pre-edit review.

### Frozen pre-edit design, proof and write set

**Frozen:** 2026-09-07T19:36:05+03:00 after two bounded read-only inventories of the existing
artifact. The current root-cause hypothesis is not a missing UI framework: the retained information
architecture already owns the required functions, but its visual tokens still read as soft
warm-card UI, several controls violate the new frequency hierarchy, phone CSS hides the Diagnostics
health entry, and some Device selections report only in the outside reviewer note instead of the
240x135 product surface. Those are P6-01 artifact defects; production and later P6 rows do not own
them.

The exact artifact write set is:

1. In the existing `<style>` block only, change the shell/accent tokens so primary and generic
   interactive emphasis is teal rather than red; make the navigation rail and existing data/code
   wells graphite with ivory content; reduce existing control/panel/dialog radii; remove the menu and
   selected-navigation shadows; retain native browser focus behavior and add only a pressed-state
   inset; make Device navigation/prose sans-serif while keeping code, file data and terminal output
   monospace. Red remains exclusive to existing danger/error/delete classes. No spacing grid or
   breakpoint family changes.
2. Add only three shared grouping classes: `cm-owner-actions` for a compact local group,
   `cm-owner-disclosure` for a static rare-action disclosure and `cm-owner-danger` for its separated
   danger subsection. Reuse existing `cm-row`, `cm-stack`, `cm-settings-section`, `cm-menu` and
   `cm-danger` owners everywhere else.
3. In existing render strings, keep Chat unchanged; group Project Import/Export under one
   `Project transfer` disclosure while New Project remains primary; keep text Save primary and make
   Download primary for selected binary/bundle files without duplicating it in More actions; split
   Wi-Fi discovered-network and selected-network content while keeping the one state-dependent
   Scan/Refresh owner and Connect beside its fields; put hidden/manual Wi-Fi, firmware maintenance
   and Diagnostics export behind named static disclosures; give API profile, model preset and SSH
   profile secondary actions compact owner-local groups and put their unchanged Delete action behind
   explicit target-bearing confirmation/disclosure; wrap changed-host-key Forget in an explicit
   confirmation disclosure. Preserve every existing `data-owner`, `data-action`, `data-open`, field
   ID and dialog focus-return owner.
4. At `<=640px`, make the existing context bar a two-row layout and keep the single Diagnostics
   health, Pending and Session controls visible; do not duplicate or rehome them. Preserve the
   intentional collection/detail route hiding and exact Back restoration.
5. In the existing Device renderer/handler only, preserve every screen ID, item string, item order,
   parent and key meaning. Add visual group breaks derived from existing item meaning, show the
   already-owned `deviceStatus` in the Device footer, map each currently unmapped visible list action
   either to an existing screen or to a concise visible product-state outcome, and make Enter on the
   existing confirmation/input screens return through their existing parent with an explicit visible
   outcome. `Forget trusted host key` is the one existing list action that additionally requires an
   exact-target two-step transition on `SshProfileActions`: first Enter stores and displays a
   confirmation for `Field gateway` in the existing `deviceStatus`/footer, Esc clears it without an
   outcome or navigation, and a second Enter produces the explicit visible forgotten-key outcome.
   This is presentation-state reachability, not a new route, data model or simulated external effect.

The artifact resource ceiling is 180 KiB (184,320 bytes), leaving 7,838 bytes above the superseded
176,482-byte baseline. It must remain one self-contained fragment with one inline script and no
external asset, font, framework, request, storage, timer or backend clone.

The smallest proof is frozen as follows:

- a source inventory must map every Web and Device control to exactly one existing owner, handler,
  dialog, existing screen or visible Device outcome, with no duplicate action and no reviewer-only
  response counted as product behavior;
- rerun the retained identity-bound Project/Chat/File/SSH/API/preset CRUD, owner-local collection
  loading/empty/error/retry/EOF, auth/degraded/provider/import/QR/long-file/mobile-Python and required
  Web/Device route observations on one new exact SHA;
- traverse Chat, Shared Files, Terminal and Settings at 1280x720, 900x720, 720x450, 640x720,
  390x780, 390x844 and 320x568; verify every rendered control is reachable and owned, health remains
  visible at and below 640 px, no horizontal overflow/overlap/closed-menu exposure occurs, and capture
  desktop, 640 px and 320 px screenshots;
- traverse every Device screen through the separate 240x135 model; verify selected/action/group
  hierarchy, key outcomes and bounds without treating the scaled reviewer frame as shipped pixels;
  for `Forget trusted host key`, verify that initial activation has no effect, Esc preserves the
  selected profile/key state and clears confirmation, and only the second explicit Enter produces the
  exact-target visible outcome;
- repeat the six retained long-dialog, normal/fullscreen-Terminal/Escape and exact focus-return checks,
  add 640 px, re-evaluate contrast and red-use semantics, parse the script, scan self-containment and
  size, and repeat hostile SFTP output tests. Native 200% text remains explicitly unverified unless a
  legitimate user/browser scaling control becomes available.

Non-goals are any new framework, screen/route/ID, schema, asset/font, storage or backend behavior;
ornamental screws, labels or scales; gradients, glow, blur or effect shadows; animation; a second
responsive model; action removal; renamed Device items; production/test/build/upload/Device work; or
P6-02/P6-03/P6-04 implementation. This freeze is ready for one independent pre-edit review and is not
authorization to edit the artifact until that reviewer returns GO.

The first pre-edit reviewer returned `STOP` at `2026-09-07T19:45:49+03:00` only because the frozen
generic Device-outcome rule did not guarantee confirmation for `Forget trusted host key`. The exact
two-step `deviceStatus`/footer transition and confirm/cancel proof above are the complete correction;
the reviewer may recheck this blocker once. No artifact edit has started.

### Exact instrument-style artifact evidence and Architect-review request

**Evidence frozen:** 2026-09-08T00:19:35+03:00. The original pre-edit reviewer rechecked only its
host-key-confirmation blocker against the frozen design and returned `GO-to-edit`. The resulting
task-owned artifact at
`C:\Users\84vs1\.codex\visualizations\2026\09\02\01a06386-22d5-7833-bb82-40a4f499f52e\p6-01-neutral-coverage-ia.html`
is SHA-256 `437FCE530511D4CF421D70B3E4EB2E4F7F1E414805B5ECB672B0C19DF721D154`,
184,263 bytes, 57 bytes below the 180 KiB ceiling. The repository production/test boundary, P6-02,
build, upload and physical Device remained frozen.

Observed evidence on this exact hash is:

- The fragment has one parsing inline script and one inline style, no document wrapper or external
  resource, and zero executable fetch/XHR/WebSocket/EventSource/`sendBeacon`, browser-storage or
  timer path. The DOM has zero duplicate IDs, ownerless product controls, external-resource nodes,
  gradient/shadow/filter offenders or browser warning/error entries. The retained review footer
  explicitly states that no backend action executes.
- The warm enamel/ivory work surface, graphite instrument zones, muted teal selection/primary state
  and amber warning state are retained. Red is confined to existing danger/error/delete semantics;
  ordinary Device prose/navigation is sans-serif while terminal/data text remains monospace. The
  selected `Forget trusted host key` state measures 7.32:1 contrast. Current-hash screenshots were
  inspected at desktop, 640 px, 320 px and the separately scaled 240x135 Device model.
- Chat, Shared Files, Terminal and Settings were rendered at 1280x720, 900x720, 720x450, 640x720,
  390x780, 390x844 and 320x568. All 28 completed cases had zero clipping-aware control overlap,
  occlusion, ownerless product control, closed-menu exposure or root horizontal overflow. The only
  raw mobile over-width text was the deliberately hidden/ellipsis/nowrap heading or status line;
  the root widths remained exact. At 720x450 the ready file editor was 23 px high, ended 16 px before
  the footer and 28 px before `Next`. Linked and full-storage notice content is deliberately clipped
  by the owning `overflow:auto` body rather than painted over the footer; focusing the full-storage
  editor scrolled that body to 39.2 px and exposed the editor at y=265..282 before the y=299 footer,
  again leaving 16 px. A bounded read-only layout reviewer confirmed that no further CSS change is
  required and that a flex replacement could collapse the constrained editor or disturb binary and
  bundle fill behavior.
- Web preset selection changed the form to `Fast` / `gpt-5-mini` / `1024` while the active Project
  remained `baseline-model` / `3072`; `New preset` also left those Project values unchanged. Only
  `Apply to active project` changed the Project to `gpt-5-mini` / `1024`. The handler update object is
  exactly `{model:p.model,output:p.output}`, the Project record schema has no preset-reference field,
  and the success message names `Fast`, `Field notebook`, model and output. With `Shared storage full`,
  the visible error named `Field notebook` and preserved `failure-model` / `3333`.
- On Device `MODEL PRESETS`, activating `Field notes` or `New preset` changed only the visible local
  outcome and preserved Project `device-baseline` / `3456`. The complete label
  `Apply to active project` fit the 240x135 screen. First Enter displayed
  `Apply to Field notebook? Enter again · Esc`; Esc cleared the prompt and preserved the Project.
  A fresh two-discrete-Enter path produced
  `Applied Field notes to Field notebook: gpt-4.1-mini / 2048`; the native keydown path passes
  `event.repeat` and the handler rejects repeated Enter/Esc. Full-storage confirmation instead
  displayed `Apply failed; Field notebook unchanged.` and preserved `device-fail-model` / `3555`.
- At both requested 320 px and 640 px widths, Terminal Back hid the task and Connect control; selecting
  exact profile `lab` exposed both, rendered heading `Lab server`, and focused `cmViewHeading`. The
  direct terminal-input path now shares the existing 8,192-character bound with submitted input and
  paste: an 8,192-character buffer remained 8,192 after direct `Z` with `Z` at the tail, and Backspace
  reduced it to 8,191. Source inspection found exactly three `.slice(-8192)` paths.
- The blocking-auth dialog remained open with its close control hidden after three native Escape
  presses, and Unlock closed it. QR rejected invalid UTF-8, empty text and 321 bytes while accepting
  the 14-byte valid value. At 320x568 the manual Python list and editor remained mutually exclusive;
  `sample.py` opened in the main pane, restart returned `Restart confirmed · device not restarted`,
  and the root stayed 288/288 px. The Device host-key Forget path again showed its exact first prompt,
  Esc cancel, fresh first prompt and second-Enter `Forgot key: Field gateway` outcome.
- The complete current 88-screen Device selection pass had no missing title, selection or body-bound
  anomaly. The retained full Device item and Web identity/CRUD, owner-local collection, import,
  degraded-provider/SD, long-file, SFTP, focus-return and required-route traversals remain causal from
  immediate predecessor SHA-256
  `5E7BC5E45E9D0783631C0520AC570B1880E7EC6AFF36DE6B0B4066011361142E`: the only later behavioral
  edits are the directly re-executed preset Apply, mobile SSH-selection and terminal-boundary paths;
  the remaining deltas are the verified radius/reviewer-note compaction and file-row contraction.

The original final-code reviewer rechecked only its SSH-selection and direct-terminal blockers on the
exact frozen hash and returned explicit `GO`. A different fresh proof red-team rechecked only the
Web/Device preset-Apply blocker on the same exact hash and returned explicit `GO`, including inert
selection/creation, two-discrete-Enter/repeat semantics, failure preservation, no preset reference,
240x135 fit and size budget. Native 200% text remains explicitly **unverified** because the available
browser surface exposes no legitimate user/browser scaling method; no DOM/style test injection was
used. This is an evidence-ready request for Architect review, not P6-01 completion, staging or commit
authority.

Exact-owned review cleanup completed at `2026-09-08T00:19:35+03:00`: the temporary viewport override
was reset; task-owned in-app browser tabs 2 and 3 were closed; all task-owned preview processes were
stopped; and ports 49578, 54134, 57562, 56894, 61509, 51223, 54761, 53271, 62049, 52202, 60740,
64901, 63335 and 55567 had zero listeners. No other browser tab or process was changed. No Device
fixture, API credential or Wi-Fi configuration was read or changed.

### Architect closure STOP and correction lock

**Recorded:** 2026-09-08T00:51:51+03:00. Architect personally reviewed exact artifact SHA-256
`437FCE530511D4CF421D70B3E4EB2E4F7F1E414805B5ECB672B0C19DF721D154` and returned mandatory
closure `STOP`. Its USSR measuring-instrument visual language is accepted and frozen: the warm
ivory/painted-metal surfaces, graphite instrument wells, restrained teal/amber, red-only danger
semantics and modern readability must not be redesigned. P6-01 remains the sole `in_progress` row;
P6-02 through P6-08 remain `pending`; production, repository tests, staging, commit, build, upload
and physical Device work remain frozen.

The correction is limited to the existing task-owned HTML/CSS/JS artifact and this trace and owns
exactly these seven defects:

1. `Clear messages` leaves `chat.cleared=true`, so a later accepted Send stays behind the empty
   transcript. Accepted Send must clear that flag and display the new message.
2. Canceling uploaded Project-bundle review retains only a filename and offers no owner-local resume
   or validate path. The actual selected upload must remain in presentation state and Import must
   expose truthful Resume review/Validate without a new route or framework.
3. Reused Device collection screens are not bound to selected identity/type: Project, Chat, file,
   SSH, network/source/SFTP and Model Preset paths reuse hard-coded sample identities; binary
   `capture.bin` exposes text actions; `Fast` is never bound before Apply. Existing screen IDs, item
   strings and routes must remain while their render/handler data becomes selection- and type-bound.
4. Web file-window `Next` changes only a counter over unchanged full content, Save replaces the full
   file, and Save copy as converts every source to text. At least two distinct 1 KiB windows must be
   modeled; Save changes only the visible window and preserves the other; copies preserve selected
   text/binary/bundle kind and content semantics.
5. Native dialog close/reopen can let a stale close event clear the newly opened dialog state;
   in-dialog transitions must avoid close/reopen or guard that exact event. Document key handling
   must not consume Enter from native controls, and an open dialog must own Escape before terminal or
   Device background shortcuts.
6. The visible Waiting session summary is future P6-03 behavior without a P6-03 marker. Only the
   future Waiting/lifetime state receives that marker; shipped authentication states remain unchanged.
7. Constrained-height layouts are not operable: the prior categorical no-overlap claim missed
   collapsed Chat/list/transcript, Shared-file list/editor, Python list/output and Device screen/key
   geometry at 720x450, plus the 320x568 Chat transcript. Existing flex/grid min-size and overflow
   owners must be corrected without a new breakpoint family or a visual-language change.

The categorical predecessor-evidence statements at lines 1414-1424 and their causal-reuse claim are
withdrawn for these affected transitions and constrained layouts. They remain historical observed
measurements only, not acceptance evidence. Before the first artifact edit, the primary must finish
the producer/consumer and persisted-presentation inventory, freeze the minimal typed state/transition
design, exact selector/function write set, size recovery and direct proof matrix, and obtain one
bounded independent pre-edit design review. Closure requires one new exact SHA, direct proof of the
seven corrected transitions, 720x450/320x568/240x135 geometry, syntax/self-containment/size/console/
style regression, a fresh bounded code/proof review, a separate fresh visual review, exact-owned
cleanup and another personal Architect GO.

### Frozen Architect-STOP correction design and proof

**Frozen:** 2026-09-08T01:10:34+03:00 after two bounded read-only inventories of exact STOP
artifact SHA-256 `437FCE530511D4CF421D70B3E4EB2E4F7F1E414805B5ECB672B0C19DF721D154`.
The observed defects are local to the artifact's existing presentation state, renderers, delegated
handlers and constrained grid owners. No production, persistence, backend, route-family or later-row
owner is implicated.

The minimal state and transition design is frozen as follows:

1. Accepted `#cmComposer` submission sets the selected chat's existing `cleared` field to `false` in
   the same update that records the accepted message. Empty or rejected submissions do not change it.
2. Project Import adds one nullable presentation-only `importUpload` value containing the selected
   browser `File`. Upload Review retains that object; Cancel is a real dismissal but does not erase
   it; reopening the existing `project-import` dialog exposes `Resume review` to the existing
   `project-import-review` route and its existing Validate action. Shared-bundle selection and a
   successful import clear the upload object. Validate and Import reject a missing or mismatched
   upload without changing the active Project. No filename-only upload is accepted.
3. The existing file-record `content` field becomes a list of bounded UTF-8 text-window strings;
   binary and Project-bundle records have no text windows. The selected seed text file has two
   distinct generated 1,024-byte ASCII windows. `filesView()` renders only `content[fileSection]`;
   Previous/Next clear the old editor draft; Save rejects a replacement over 1,024 UTF-8 bytes and
   replaces only the selected list element while preserving every other window and the current
   section. QR joins text windows. New/upload producers use the same representation, and Save copy
   as clones the selected record's kind, size, bytes and content rather than converting it to text.
4. Device collection rows project stable identities from existing Project, Chat, file, SSH, API
   profile, model-preset and import state; only small immutable Wi-Fi/source/remote-entry records plus
   `deviceWifiId`, `deviceSourceId` and `deviceSftpDirection` are added where no selected identity
   exists. One pure row projection binds a selected stable ID before following the existing route;
   one pure screen projection derives existing screen titles, text and action visibility from that
   selected record. All existing screen IDs, parents, action strings and routes remain. Binary and
   bundle file actions omit text-only operations. Device preset selection binds `modelPresetId`
   before the unchanged two-Enter Apply path. No parallel generic selection store is added.
5. The three Project mutations that currently close and immediately reopen a dialog instead commit
   while the modal stays open and replace it through existing `showDialog()`. Genuine close events
   retain their current listener. Document key handling keeps blocking-auth Escape first, then gives
   every open dialog exclusive key ownership before terminal/Device shortcuts; outside a dialog,
   native interactive controls retain Enter before Device handling.
6. Only the visible Waiting session summary receives the existing `P6-03` gap marker. Ready,
   expired, locked, lockout and invalid-auth summaries retain shipped wording and no new marker.
7. At the existing `max-width:740px` boundary, current collection/task grids protect one
   control-height middle viewport and let their header/footer owners shrink and scroll; current file,
   Python and Device owners receive the smallest min-height/overflow corrections. At the existing
   mobile boundary the file body scrolls instead of clipping. `cm-device-wrap` uses safe centering so
   over-tall content starts at a reachable scroll origin. No breakpoint, color, radius, typography,
   spacing language or navigation model is added.

The exact artifact write set is the existing style rules for `cm-collection`, `cm-task`, their
header/footer owners, `cm-file-body`, `cm-file-editor`, `cm-python-side`, `cm-python-files`,
`cm-python-main` and `cm-device-wrap`; seed/state and selected-record helpers; `filesView()`,
`render()`, the four Project Import dialog cases, Device row/screen projections, `renderDevice()`,
`deviceKey()`, `scenarioChange()`, affected `action()`/`genericConfirm()` branches, and the root
click/submit/keydown delegates. The HTML shell, DOM IDs, Web route set, Device screen-ID set,
production files and repository tests are excluded.

The 184,320-byte ceiling is unchanged. Space will be recovered only by removing observed unread
`fileKind`, `fileSaved`, `settingsSaved` and `deviceImportStep` presentation fields, removing the
unreachable `choose-import` action, deleting the three faulty close calls, and consolidating
later-overridden duplicate declarations inside the existing 740/640 media rules. Consolidation must
preserve the prior computed style except for the frozen constrained-height corrections; no product
function, state option or proof route may be removed to meet the ceiling.

The smallest direct proof on one new exact SHA is:

- Clear → Confirm → Send displays the accepted message and restores the non-cleared transcript;
- Upload Project bundle → Review → Cancel → reopen Import → Resume review → Validate works from the
  same retained `File`, while an absent upload cannot validate/import and activation occurs only
  after successful Import;
- Device directly binds Bench notes, Collecting observations, `capture.bin`, Lab server and Fast,
  plus Guest Wi-Fi, ESP32 power-management source, remote `capture.bin`, Field backup API profile and
  the existing Project-bundle row; every derived target is visible, `capture.bin` has no text action,
  and Fast is selected before Apply;
- Web file Next shows a distinct second 1 KiB window, saving it preserves the first, navigation does
  not leak an unsaved draft, and text/binary/bundle copies preserve kind/content semantics;
- in-dialog Project mutation followed by pagination retains dialog ownership; native button Enter
  cannot trigger Device input; open-dialog Escape cannot change terminal fullscreen or Device state;
- the P6-03 marker appears on Waiting/lifetime only and not on shipped authentication summaries;
- at 720x450 and 320x568, direct geometry proves a full control-height list/transcript viewport,
  usable file editor/footer and Python list/source/output, zero bounding-box overlap or root horizontal
  overflow; at 720x450 the Device scroll origin exposes its caption/screen and scrolling exposes all
  keys/detail while the screen retains 240:135 bounds.

After those transitions, rerun syntax, duplicate-ID/ownership, self-containment, size, console,
closed-menu, style-token, contrast/red-use and exact-owned cleanup checks. Then obtain one fresh
bounded code/proof review and a separate fresh visual review limited to these corrections before
requesting another personal Architect closure review. This freeze is not permission to edit until
one independent pre-edit reviewer returns explicit GO.

### Architect-STOP correction pre-edit GO clarification

**Recorded:** 2026-09-10T02:39:38+03:00. The independent bounded pre-edit review returned
`GO-to-edit` after requiring these two exact clarifications; Architect accepted them and requires no
additional pre-edit review round:

1. For every text file, `content` is the complete authoritative modeled content as a non-empty list
   of UTF-8 windows. Section count, cumulative displayed byte offsets/ranges, total bytes and visible
   size are derived only from that list; the former 6,420-byte sample metadata cannot survive when
   the content is two 1,024-byte windows. Save replaces only `content[fileSection]`, recomputes the
   derived metadata, retains that section and preserves every other window. Navigation clears only
   the outgoing editor draft. Save copy as clones text windows and preserves the selected kind;
   binary and Project-bundle files have no editable text windows. This remains presentation-only and
   does not simulate backend or storage behavior.
2. A single control-height middle track is not an acceptance oracle because it would permit the
   already rejected 44–47 px Chat slit. Existing header/footer/composer/scroll owners and the
   existing 740/640 boundaries must instead leave a readable, scrollable content region with
   complete visible text lines and reachable surrounding controls. Direct visual and geometry proof
   at 720x450 and 320x568 must explicitly reject the prior Chat/list/file/Python slits and Device
   overlaps. No arbitrary new pixel threshold, breakpoint, framework or visual-language change is
   authorized.

All other frozen corrections, write-set exclusions, size ceiling and proof obligations remain
unchanged. This is edit authority for the existing seven-defect artifact correction only; it is not
P6-01 completion, staging, commit or P6-02 authority.

**Clear → Send clarification — 2026-09-10T02:42:42+03:00.** Direct source inspection showed that
the earlier literal `cleared=false` prescription alone would resurrect the seed/history transcript
that Clear had removed, while the current Send path also discards the entered value. The binding
behavior supersedes that implementation detail: Clear presents an empty transcript; the next
accepted Send presents exactly the newly entered message without restoring cleared seed/history;
selected-chat settings remain unchanged. Implement only the smallest presentation-local accepted
text plus cleared-history render state inside the existing Chat owner. Do not add a conversation
engine, log, backend/storage simulation, action, entity, route or framework. This clarification and
the UTF-8-window/geometry clarifications are truthfulness corrections to existing P6 controls, not
scope expansion; all work remains strictly inside ROADMAP Phase 6 and the seven recorded defects.

**Device inspected/active identity clarification — 2026-09-10T03:31:00+03:00.** A bounded
read-only inventory found inherited Device semantics missed by the pre-edit review. Architect
verified the producer/consumer boundaries and returned `GO-to-edit` inside existing defect 3, with
no P3/P4 reopen, new row or new review cycle. Add only specific inspected Project and Chat IDs beside
the existing active `projectId`/`chatId`; inspection and Esc leave active IDs unchanged, existing
Open actions perform activation, action renderers use inspected records, and the live Chat/composer
uses active records. Classify record and action rows explicitly and do not use cascading literal
replacement or a generic selection store. For SSH, retain only existing `sshProfileId` as inspected
identity and `sshDefaultId` as default/active authority: Make default copies inspected to default;
Connect, SFTP and Edit refuse an inspected non-default profile; accepted Connect/SFTP and top-level
key install resolve the default; Forget/Delete target inspected. Successful Device import reuses
`newProjectRecord` plus existing insertion/activation primitives only after the existing successful
Import transition; select/validate/cancel leave the active Project untouched. Remove the artifact's
incorrect delete-profile effect that clears matching Project/Chat SSH ceilings; actual deletion
removes the profile and refreshes while stale ceilings remain fail-closed. No third SSH identity,
parser, transaction, backend simulation, new UI control or broad budget refactor is authorized.

**Terminal input presentation clarification — 2026-09-10T05:03:11+03:00.** Architect relayed the
user's correction of the already-approved terminal boundary: ordinary keyboard input belongs
directly to the existing focusable terminal output, while the separate `Type terminal input` / `Send
input` helper is shown only when a coarse pointer makes touch entry useful. A hybrid touch-plus-
keyboard device retains both paths; viewport width and pointer media queries must not be treated as
proof that a hardware keyboard is absent. Printable input, Enter, arrows, Tab, Ctrl combinations and
paste remain within the existing direct terminal owner, and accepting Connect/trust returns focus to
that owner so typing can start immediately. Open dialogs and unrelated native inputs retain their
existing exclusive key ownership. This is a focused P6-01 artifact correction under the existing
Terminal CSS/input/focus owners, not a detector, framework, setting, route, terminal engine or P6-05
implementation. Add only focused desktop, touch and hybrid observations to the existing terminal
proof; do not restart the already-observed seven-defect acceptance paths.

**Residual constrained Files observation — 2026-09-10T06:12:35+03:00.** Direct browser geometry on
artifact SHA-256 `663E2BD1DD1AC6E6B91E41B9AB3A1C48131503CB618907946B3502510E265B77`
(184,314 bytes) removed the prior footer overlap but left the 720x450 selected-file editor only
49.2 CSS pixels high. With its existing border, 8 px vertical padding and 14 px / 1.45 text, that is
one complete text line plus a clipped second line, so defect 7 remains owned by P6-01 and the
geometry result is not acceptance evidence. The smallest correction is to give the existing
`cm-file-body` editor track a three-line-height minimum while retaining its current body scroll owner
and reachable footer; the existing 640 px rule continues to use its content-driven remaining track.
Only focused 720x450 and 320x568 selected-file geometry and screenshots are required afterward.
The same constrained-geometry hypothesis remained active from the 05:36 checkpoint through this
observation; 36 minutes of wall time is a conservative upper bound including browser/tool waits, so
no 60-active-minute pivot threshold has been reached.

**Focused Files correction evidence — 2026-09-10T06:16+03:00.** Artifact SHA-256
`10EE88F436960681D298307FE319AD625B7166AE0AB09074D5FF35758854E9D9` is 184,316 bytes.
At 720x450, the selected text editor measured 60.9 px total, 42.9 px between its border and padding,
and 20.3 px line height: two complete text lines plus remaining space. Its bottom was 306.3 px, the
existing file footer began at 310.6 px, and root client/scroll widths were both 688 px. At 320x568,
the editor measured 110.85 px total, 92.85 px between border and padding at 23.2 px line height, its
bottom was 377.0 px, the footer began at 383.0 px, and root client/scroll widths were both 288 px.
Focused screenshots showed the editor content and Previous/section/Next footer readable at both
sizes. The same `cm-file-body` owner now supplies the three-line-height desktop minimum; the existing
mobile rule still assigns the remaining track. No new breakpoint, footer/action owner or horizontal
scroll owner was added.

**Final static/runtime reconciliation — 2026-09-10T06:20+03:00.** The same 184,316-byte SHA parsed
as one inline script and remained an HTML fragment with no external resource/API dependency.
Focused static checks found the exact 740/640 constrained-owner rules and non-recursive `gapAttr`, no
corrupted combined task/collection rule, no gradient/glass/blur/shadow vocabulary, one declared
danger color/background pair, and text/surface contrast ratios from 5.69:1 to 13.30:1. Clean browser
loads at 1280x720, 720x450 and 320x568 traversed Chat, Shared Files, Terminal, Settings, Python and
Device; the phone run additionally traversed both Python list and detail routes. They produced no
page/console errors, runtime duplicate IDs, missing visible product action owners, exposed closed
menus or root horizontal overflow. Architect explicitly limited the post-Files rerun to focused
Files geometry because the final two-byte change touched only the existing `cm-file-body` minimum;
the immediately preceding seven-transition and terminal observations remain the accepted unchanged
boundary evidence rather than being repeated solely for that CSS correction.

**Final-review STOP and frozen correction batch — 2026-09-10T06:41+03:00.** Personal Architect
review and the fresh visual reviewer independently rejected SHA-256
`10EE88F436960681D298307FE319AD625B7166AE0AB09074D5FF35758854E9D9`: at 720x450 the selected-file
body and textarea were competing scroll owners and the nominal 42.9 px inner editor showed a
clipped meaningful line; at 320x568 the three-column task header left only 28.86 px for the
110 px filename and zero width for the selected Terminal profile identity. The fresh code reviewer
also found that Connect, Cancel trust, Review host key, Trust can focus the terminal and then have
the queued native dialog `close` handler steal focus because the vanished review button is still the
dialog invoker. These are concrete P6-01 defects in existing Files layout, shared task-header and
terminal trust-focus owners; no foreign row is reopened.

One coherent correction batch is frozen before editing. The base `cm-file-body` will drop its forced
100% height and own clipped layout overflow while its existing textarea remains the sole content
scroll owner; the 640 px rule will remove its redundant `align-content` declaration and replace its
outer automatic overflow with the same clipped owner, retaining the existing three-line 740 px
track and remaining-height 640 px track. At the existing 359 px boundary, the task header will use
two columns, place its full-width identity on the first row, and let the existing Back and action
owners occupy the second row; this corrects Files and Terminal without another breakpoint, DOM
control, typography rule or navigation model. Trust acceptance will first render the connected
Terminal, bind the existing dialog invoker to that newly rendered terminal output, and close the
dialog so the existing shared `close` handler delivers final focus on both first-open and
Cancel/reopen paths. It adds no timer, input detector, state, route or terminal behavior. Space is
recovered only from the harmful file-body height and redundant mobile alignment/overflow
declarations; the 184,320-byte ceiling remains binding.

Only affected proof will be repeated on the resulting exact SHA: 720x450 Files and 320x568 Files plus
Terminal geometry/screenshots, including one Files scroll owner, readable identities, useful editor,
reachable actions/footer, zero overlap/root horizontal overflow, and fine/coarse/hybrid Terminal
presentation; then Connect -> Cancel trust -> Review host key -> Trust must leave
`cmTerminalOutput` focused and accept direct typing. Syntax, self-containment, size and browser
console checks remain proportional final guards. The constrained-geometry hypothesis clock was
paused from 06:28 through this bounded-review wait; 52 minutes remains the conservative active-work
upper bound on resumption. This is not completion, staging, commit or P6-02 authority.

**60-minute layout pivot — 2026-09-10T06:52+03:00.** The first focused observation of corrected
SHA-256 `5BF4DE9CD36B61E0B651ECD63832FED46ACF3588269B5DCA8D0F65443A0FDD52`
(184,307 bytes) disproved the initial file-body ownership result. At 720x450 the later 740 px
direct-child rule won the cascade and restored `overflow:auto`; the body remained 122/134 px
client/scroll height while the textarea remained 59/178 px, and its 60.9 px outer track still left
only 42.9 px of text area. The conservative clock bound crossed 60 minutes even though tool and
review waits make active time lower, so incremental minimum-height adjustment stops here.

The materially different approach is an aggregate Files composition correction: exclude only
`cm-file-body` from the existing 740 px direct-child overflow assignment so its base clipped owner
wins; give the textarea track four line heights; move the already-defined compact file-footer rules
unchanged from 640 px to the existing 740 px boundary; move the existing 6 px file-body gap and
bottom padding to that boundary; and shorten the redundant body note to the single-line equivalent
`Project links do not own files.` The textarea is then the sole file-content scroll owner while the
header, body and footer natural sizes fit the existing task grid. The already-applied two-row 359 px
identity layout and dialog-invoker terminal focus handoff remain unchanged. This pivot changes no
breakpoint, control, route, state, palette, framework, persistence claim or acceptance oracle; its
same focused proof must pass before any wider reconciliation.

**Pivot geometry checkpoint — 2026-09-10T06:56+03:00.** On SHA-256
`CB668BAD4F9137C35CB8C6B98CCA9FCEBEB4A7A2A05569D7C4C2EDCE9696BB41`
(184,292 bytes), 720x450 Files now has a non-scrolling 401x122 px file body, an 88 px inner
textarea with complete heading, blank line and two meaningful lines, and a non-scrolling 401x44 px
footer. The sole remaining task-side scrollbar is exactly assigned: the header is 48 px client but
52 px scroll height because its 8 px vertical padding leaves the natural header four pixels larger
than the constrained grid track. Inside the same frozen existing task-header owner, reduce only the
740 px vertical padding from 8 px to 6 px so its natural and assigned heights agree; this does not
affect the later 640/359 px header rules. No other result or oracle changes.

**Phone geometry checkpoint — 2026-09-10T07:03+03:00.** On later SHA-256
`F304D8A59BF417069D6568D37BB15DE8CFFD8D43F3B0FFDFC73E9791A0861760`
(184,292 bytes), 720x450 Files passes the pivot geometry: header, body and footer client/scroll
heights agree at 48/48, 122/122 and 44/44 px; only the 88/178 px textarea scrolls, three complete
text lines are available after padding, all actions/footer controls are visible, and root width is
688/688 px. The first 320x568 observation proves the identity correction (246 px available for both
filename lines), a non-scrolling 269x122 px file body, an 89 px inner editor with three complete
lines, and a non-scrolling footer, but rejects the header: its 76/88 px client/scroll height lets the
Back/actions row extend eight pixels into the body. The existing 6-line body minimum and editor are
not reduced. Inside the already frozen 359 px two-row header, remove only its 4 px inter-row gap and
the title's inherited 4 px internal gap; reduce the already-moved compact file-footer vertical
padding from 6 px to 4 px. Those exact 12 pixels let the natural header, unchanged body and footer
fit the existing task height without clipping. No content, control, breakpoint or state changes.

**Phone scrollbar checkpoint — 2026-09-10T07:06+03:00.** SHA-256
`AB57D9C5CC23E296CDF8F5468A79985D022FD641CBC599A7887675016ACDC275`
(184,296 bytes) gives the 320x568 header exact 80/80 px client/scroll height; Back/actions end at
259.75/261.75 px, the body begins at 265.20 px, and no overlap remains. The generic 740 px
`overflow:auto` owner nevertheless renders a persistent platform scrollbar gutter and arrows on
this non-scrolling narrow header, reducing its 269 px box to 254 px client width. Because exact fit
is now observed and the 359 px header already owns this reflow, set only that header's overflow to
visible so it has neither clipping nor a redundant scroll control. The body stays clipped and the
textarea stays the sole Files content scroll owner.

**Scrollbar cascade correction — 2026-09-10T07:11+03:00.** Exact SHA-256
`C0171A2D76C620CCAB0A379B67377E71254E411076CDFF420FA398D8D112BDBE`
(184,313 bytes) retained the gutter because the 740 px direct-child selector gained a second class
of specificity from `:not(.cm-file-body)` and therefore still beat the later one-class 359 px
header selector. Geometry itself remained passing: header and body meet without overlap, identity
uses 246 px, Back/Save/More and footer are wholly inside their boxes, only the editor scrolls, and
root width is 288/288 px. Strengthen only the existing 359 px rule to the direct
`cm-task > cm-task-head` owner and use the initial `unset` overflow value; contract the unchanged
support copy to `Project links don't own files.` solely to retain byte headroom. This is the final
cascade assignment, not another geometry threshold or owner.

**Invalid copy contraction — 2026-09-10T07:13+03:00.** Fresh load of SHA-256
`7E75EA7D41B167D002C7C34E181A36EBFA59A06B278C551D57625E187B975F17`
(184,319 bytes) stopped before workspace render. Direct script parsing failed with
`SyntaxError: Missing } in template expression`: the contraction's ASCII apostrophe terminated the
existing single-quoted HTML fragment. This run is invalid and supplies no layout evidence. Replace
only that copy with the equally scoped apostrophe-free `Project links never own files.`; the
specificity correction and all geometry remain unchanged.

**Final phone rounding checkpoint — 2026-09-10T07:18+03:00.** Parse-valid SHA-256
`A1B89261035B3A6C1E83F8FEF4A6763860898C74EDD5E4C7A0ED392AE3CDB6C8`
(184,319 bytes) passes focused 720x450 Files: 48/48 px header, 126/126 px body, 92/178 px
textarea, 40/40 px footer, three complete text lines, one content scroll owner and 688/688 px root
width. At 320x568 the strengthened header correctly computes `overflow:visible`, uses the full
269 px width, and keeps identity plus Back/Save/More wholly separated from the body. That extra
gutter-free width changes fractional grid rounding: the 80.40 px header plus unchanged 121.80 px
body leaves the footer 39.45 px while its natural scroll height is 40 px, producing the sole
remaining scrollbar. Reduce only the existing 359 px header padding from 4 px to 3 px, freeing two
CSS pixels so the unchanged footer fits naturally. No threshold, content, scroll owner or control
changes.

**Affected pivot proof — 2026-09-10T07:35+03:00.** Final artifact SHA-256
`5F3AB8699738E350809AAFB29D21D64F2AA66FEE8D326964D22DBC6CDC0971EF` is 184,319 bytes.
At 720x450, selected `field-notes.md` has 48/48 px header, 126/126 px body and 40/40 px footer
client/scroll heights; its textarea is 92/178 px with three complete content lines after padding.
At 320x568, the same header/body/footer are 78/78, 123/123 and 40/40 px; the two-line file identity
uses 263 px, Back/Save/More remain inside the header, the textarea is 90/248 px with three complete
lines, and every header/body/editor/footer boundary is separated. Only the textarea scrolls at both
sizes. Root client/scroll widths are 688/688 and 288/288 px respectively. Focused screenshots show
readable identities, meaningful editor content and reachable actions/footer without the rejected
nested or decorative scrollbars.

At 320x568 Terminal, `Field gateway` plus `operator@192.0.2.10:22 · Connected` uses the full 263 px
identity row and the 78/78 px header is separated from the body. The exact Connect -> Cancel trust ->
Review host key -> Trust path waited through the native close event and left
`document.activeElement.id === cmTerminalOutput`; discrete `p`, `w`, `d`, Enter events appended
`pwd\n` and retained focus. A real fine-pointer browser kept the touch helper hidden and the output
focusable. A separate real coarse-pointer Chromium context exposed the 244x44 px helper while
retaining the focusable output; helper Send appended `tap\n` and a direct keyboard event appended
`h` in that same coarse presentation, proving the hybrid coexistence contract without a pointer
detector. Both modes retained the full selected-target identity, 78/78 px header and 288/288 px root
width. The render wrapper alone emitted its pre-existing CSP syntax diagnostics; there was no page
error, and the in-app browser log for the artifact was empty.

Final proportional static checks found one parsing inline script, an HTML fragment with no external
resource or API dependency, exact Files owner/cascade, 359 px identity, coarse-helper and ordered
trust-focus rules, and no gradient/blur/shadow vocabulary. Runtime inspection found no duplicate
IDs, exposed closed menus or visible ownerless controls in the affected final state. The mandatory
pivot therefore converged without new scope; only the two existing reviewers' one-time blocker
verification and Architect closure review remain before any status, staging or commit change.

**Terminal blocker verification GO — 2026-09-10T07:36+03:00.** The same fresh code reviewer that
identified the queued-close defect inspected exact SHA-256 `5F3AB8699738E350809AAFB29D21D64F2AA66FEE8D326964D22DBC6CDC0971EF`
once and returned `GO`. It confirmed that trust acceptance renders connected state, assigns the
newly rendered terminal output as the existing dialog invoker, and only then closes; the shared
queued close handler therefore focuses that connected node. Existing direct keyboard/paste owners
and their 8,192-character bound remain unchanged, and the supplied Cancel -> Review -> Trust ->
`pwd\n` observation directly covers the originally failing path. No route, dialog-key, coarse
helper, terminal-state or resource regression was found in this correction boundary.

**Prior visual-blocker verification GO — 2026-09-10T07:48+03:00.** The already-running fresh visual
reviewer completed only its one-time check of the previously frozen selected-file and Terminal
blockers on exact SHA-256 `5F3AB8699738E350809AAFB29D21D64F2AA66FEE8D326964D22DBC6CDC0971EF`
and returned `GO`. It accepted the selected Files editor at 720x450 and 320x568, the full phone
Files/Terminal identities, the fine/coarse helper distinction, and coarse keyboard/helper
coexistence. This review did not evaluate or waive the separate collection-composition defect below.

**Personal Architect collection STOP and focused mapping — 2026-09-10T07:49+03:00.** Architect's
personal final review accepted the selected Files editor and Terminal correction above and froze
those boundaries, but returned `STOP` for the existing left `Shared files` collection at 720x450.
The collection is a three-track `cm-collection` (`cm-collection-head`, the sole record-list
`cm-list`, and `cm-list-footer`). The existing 740 px direct-child rule assigns `overflow:auto` to
all three children. In the 178x214 px inner collection, the 163x67 px header has 185 px scroll
height: `New text file` starts below its 213.10 px clip edge and `Upload` follows below it. The
163x67 px footer has 104 px scroll height and clips `Load next page`; only the middle list is the
intended bounded collection scroll owner. AX presence therefore does not prove visible access.

The correction clock starts at 07:49+03:00 with one scoped hypothesis: inside the existing 740 px
boundary and Files collection markup, compact only the Shared-files header/footer composition,
leave both non-scrolling, and preserve the record list as the single limited scroll track. Existing
New, Upload, list and Load-next controls remain; no breakpoint, menu, state, route, framework,
selected-editor rule or Terminal rule is added or changed. The first experiment must show all four
owners visibly inside the collection at 720x450 and 320x568, a readable list viewport, no root or
collection horizontal overflow, and unchanged accepted selected-editor header/body/editor/footer
geometry. No new reviewer or full traversal is authorized; Architect will personally verify this
last collection boundary.

**Focused collection correction evidence — 2026-09-10T08:03+03:00.** Exact corrected artifact
SHA-256 `D0B55029E1A1CFAE0CA596AC3AF3D1B52C470A2DFD070E7D6DB95E9469C2A16B` is 184,318 bytes.
Only the existing Shared-files collection gained a scoped `cm-files` composition selector at the
existing 740 px boundary. Its header action row and footer now use their available columns, compact
padding and text, while the middle `cm-list` remains the sole bounded scroll owner. Removing only
formatting whitespace from the static product shell recovered the required bytes without changing
elements, attributes, order, text or behavior; the artifact remains below the frozen 184,320-byte
ceiling.

At 720x450 (688x418 inner), the 178x214 px collection now measures header 78/78 px
client/scroll height, list 87/133 px, and footer 50/50 px. `New text file` and `Upload` lie wholly
inside the header, `Load next page` lies wholly inside the footer, the selected first record and its
metadata are visible, the list has an ordinary vertical scrollbar, and root width is 688/688 px.
At 320x568 (288x536 inner), the 269x242 px collection measures header 76/76 px, list 114/149 px,
and footer 52/52 px. Both creation controls, two readable file identities with metadata, the list
scrollbar and Load-next control are simultaneously visible; root width is 288/288 px. Focused
screenshots at both sizes show separated header/list/footer boundaries with no overlap, clipping or
decorative header/footer scrollbar.

The frozen selected editor is unchanged on the same SHA. At 720x450 its header/body/editor/footer
remain 48/48, 126/126, 92/178 and 40/40 px; at 320x568 they remain 78/78, 123/123, 90/248 and
40/40 px, with the full 263 px identity row and 288/288 px root width. The textarea remains its sole
content scroll owner. A proportional static guard parsed the one inline script, confirmed fragment
self-containment and the exact Files collection owners; the first guard's broad `<head` substring
was classified as a harness false positive against `<header>` and replaced with exact tag-boundary
matching while production stayed frozen. The corrected guard passed, and the exact new preview
reported no browser warnings or errors. This resolves only Architect's remaining collection STOP;
P6-01 still awaits Architect's personal explicit closure `GO`.

**Exact-owned final review cleanup — 2026-09-10T08:21+03:00.** After Architect personally accepted
the final Shared-files collection boundary, the temporary browser viewport was reset and the exact
task-owned current preview tab was closed. The two exact-owned render listeners on ports 59,972 and
56,537 were stopped and both ports were verified with zero listeners. The temporary
`p6-01-pointer-proof.cjs`, `p6-01-pointer-fine.png` and `p6-01-pointer-coarse.png` files were removed;
those three plus every older named P6-01 helper/upload fixture in the cleanup inventory were verified
absent. Stale unrelated browser tabs, `.codex/`, `m[1])`, Device state, API credentials and Wi-Fi
configuration were untouched.

### Final P6-01 Architect closure and accepted transition evidence

**Completed:** 2026-09-10T08:25:46+03:00. Architect personally reviewed exact artifact SHA-256
`D0B55029E1A1CFAE0CA596AC3AF3D1B52C470A2DFD070E7D6DB95E9469C2A16B`, 184,318 bytes, the actual
owners/source, retained seven-transition evidence, focused later Files/Terminal evidence, resources,
cleanup and residual risk, and returned explicit final `ARCHITECT CLOSURE GO`. The final collection
STOP is closed at 720x450 and 320x568; the accepted USSR measuring-instrument visual language and
locked P6-01 action/surface coverage remain unchanged.

Architect accepted these already-observed transitions on behavior-bearing SHA-256
`663E2BD1DD1AC6E6B91E41B9AB3A1C48131503CB618907946B3502510E265B77`; later deltas through the
exact closure SHA did not change their handlers, and every affected later layout or Terminal boundary
was directly rechecked as recorded above:

1. Clear -> Confirm -> accepted Send replaced the empty transcript with exactly the new user message,
   did not resurrect cleared seed/history, and preserved the selected Chat settings.
2. Upload bundle -> Review -> Cancel -> reopen Import exposed Resume review for the same retained
   browser `File`; Validate preserved the active Project, only successful Import created/activated
   `Field kit`, and absent or mismatched upload state was rejected without activation.
3. Device selection bound Bench notes, Collecting observations, `capture.bin`, Lab server, Fast,
   Guest Wi-Fi, the ESP32 power source, remote `capture.bin`, Field backup API and the Project-bundle
   row to their exact derived targets. The binary file exposed no text action, Fast was selected before
   its two-Enter Apply path, and inspected Project/Chat identity did not become active before Open.
4. Web file Next showed the distinct second 1 KiB `## Departure check` window. Saving that window
   preserved the first `# Field notes` window; navigation discarded only its outgoing unsaved draft;
   text, binary and bundle copies retained their respective kind/content representation.
5. In-dialog Project mutation followed by pagination retained the open dialog and its owner. Enter on
   a native control did not trigger Device input, and open-dialog Escape changed neither terminal
   fullscreen nor Device state.
6. Only the future Waiting/lifetime presentation carried the `P6-03` gap marker; shipped ready,
   expired, invalid and lockout authentication summaries did not.
7. The accepted Chat, Python and Device constrained-layout observations retained readable scroll
   owners and reachable controls. Subsequent focused evidence closed the affected Files collection,
   selected editor, phone identity/header and Terminal fine/coarse/hybrid boundaries on the exact
   closure artifact without a new breakpoint family or visual-language change.

This is prototype-only acceptance, not firmware/backend completion or Cardputer heap/latency proof.
Runtime production, real-Device and phase-completion acceptance remain owned by P6-02 through P6-08.
Only this trace is row-owned repository content; the external prototype and disposable diagnostics
remain outside the commit. The publication window intentionally has no `in_progress` matrix row until
the exact local commit is pushed and its remote SHA is verified.

## P6-02 API-profile and model-preset pre-edit package

**Activated:** 2026-09-10T11:28:24+03:00 after P6-01 commit
`bd8668de82edb0fca344f8d76210b1cb0215334d` was pushed to
`feature/phase-6-ui-stable-baseline` and its exact remote SHA was verified. P6-02 is the sole
`in_progress` row. No production, test, build, browser or Device mutation has occurred for this row.

**Task clock and hypothesis:** the activation timestamp above is the observed timestamp of the sole
matrix activation edit and is the task-clock start. The current hypothesis is that the smallest complete
implementation is one fixed-slot NVS collection with COW only where a profile's separate metadata and
secret records require it, native single-key preset updates, `Settings` as a refreshed hot request tuple,
the existing `ProjectDocument.apiProfile` field as a stable-ID reference, and exactly one profile
resolution immediately before every model-provider request. The expected evidence is that this avoids a
second settings framework, keeps secrets out of lists and project bundles, prevents stale ordinary
settings saves from changing provider authority, makes capacity failure non-destructive, and lets presets
reuse the existing atomic `saveProject` owner.

**Thirty-minute checkpoint:** at 2026-09-10T11:59:50+03:00 the phase task reported a concrete
contract discrepancy to Architect: the accepted P6-01 Web artifact showed project-profile assignment,
the Device artifact did not, while the canonical P6-02 row and Phase 6 parity rule require both. The
same checkpoint asked for decisions on inheritance, deletion, migration, presets, discovery and the
proposed bounds rather than guessing. Architect's response was received by
2026-09-10T12:06:01+03:00 and supplied the ownership decision below. This was an ambiguity resolution,
not production pre-edit `GO`; inventory, the proof matrix and a fresh independent review remain gates.

### Locked contract and non-goals

- A configured installation has exactly one global default API profile. A blank
  `ProjectDocument.apiProfile` inherits that default. A nonblank value is an exact stable ID; malformed,
  missing, incomplete or deleted explicit references fail locally before any provider HTTP request and
  never substitute the default. Existing arbitrary dormant/imported values remain loadable and visible
  as unavailable until the user explicitly reassigns them.
- Both Web and Device expose profile create/edit, explicit `Use as default`, deletion and project
  assignment through their existing Settings/AI and Project Actions owners. Selecting a row or choosing
  `New` is inert until the named save/apply action succeeds. The P6-01 prototype remains closed and is
  not rewritten to retroactively depict this production work.
- The default profile cannot be deleted; another existing profile must first be selected explicitly.
  Any non-default profile may be deleted after the existing surface confirmation. Project metadata is
  not scanned, indexed, cascaded, rewritten or silently cleared. A surviving reference to a deleted
  profile remains unavailable until explicit reassignment.
- API profiles have exact 16-character lowercase-hex IDs, unique within the fixed collection. Profile
  names are valid UTF-8 of 1-48 bytes without CR/LF; base URLs retain the current 12-180-byte
  `https://` contract without spaces, query or fragment; API keys are write-only opaque values of
  8-512 bytes without CR/LF. Blank secret input while editing preserves the selected profile's key;
  create requires a key. The 512-byte ceiling contains the existing Web Console's 192-byte input
  contract while bounding the new COW peak; an oversized legacy singleton is never truncated or deleted.
- From the first P6-02 firmware boot, ordinary `saveSettings(const Settings&)` persists only
  non-provider settings and cannot write `assistant/api_key`, `assistant/base_url` or profile records in
  any provider-store state. The dedicated provisioning/bootstrap commit is the sole scalar-form
  credential ingress and creates or updates the default profile before its existing restart. Device and
  Web profile commits and the default switch use dedicated profile operations. The existing serial
  `APIBASEHEX` diagnostic may update the current default through that dedicated operation only in `Ready`;
  it rejects `Unconfigured`, `LegacyRetained` and `AuthorityUncertain` before any NVS write. A successful
  edit of the active default or a successful default switch reloads the Device `settings` or Web
  `consoleSettings` hot tuple after durable commit; ordinary failures retain the old tuple, while
  `AuthorityUncertain` blocks provider use until boot resolves actual authority.
- Only an absent schema key permits pre-authority behavior. Legacy migration validation or capacity
  rejection returns the typed `LegacyRetained` state: normal requests continue using the unchanged
  canonical singleton, a structured warning and profile-management response expose only the reason and
  never secret material, the same complete migration may be retried, and no schema marker is issued.
  This is an explicit transition authority, not fallback from an authoritative new format. A present
  schema key with a wrong NVS type/version is a hard storage error and never reopens legacy authority.
- The implementation limit is three API profiles. This is a provisional capacity lock, not retained
  measurement: it closes only after the final-core Device evidence shows the real aggregate NVS state,
  all three maximum-shape slots, one maximum-shape COW update and the low-capacity rejection path.
- Model presets are value templates only. Up to six fixed slots hold exact 16-character lowercase-hex
  IDs, valid UTF-8 names of 1-48 bytes, valid UTF-8 model IDs of 1-120 bytes without CR/LF, and output
  values from 128 through 8192. There is no preset default or persisted project reference. `New` and
  selection are inert; `Apply` copies only `model` and `maximumOutputTokens` into a freshly loaded
  project through `saveProject`, and any failure leaves the previous project values authoritative.
- Global model discovery resolves the global default profile. Project, Chat and preset discovery resolve
  the active/selected project's effective profile. Callers pass only a saved stable reference or project
  scope; keys never enter a URL, request argument, JSON response, project file, bundle or diagnostic.
  The global `Settings` object is not mutated to impersonate a project profile, and there is one profile
  resolver shared by Device and Web request/discovery paths.
- Updating a profile name alone leaves its provider-authority revision unchanged. A base-URL or secret
  change increments that revision. A same-boot Pending continuation captures a non-secret typed authority
  identity and re-resolves the secret just in time: `Ready` uses effective profile ID plus authority
  revision; `LegacyRetained` uses a fixed legacy kind plus a boot-local generation counter, never a secret
  or secret-derived hash. Successful same-boot migration changes the kind and stales legacy Pending. A
  project reassignment, deleted profile, changed base URL/key, or default change for an inheriting project
  likewise stales Pending before provider HTTP; an explicit project's unrelated default change does not.
- STT, Search and TTS settings remain independent. This row adds no paginated collection, profile
  framework, provider plugin, per-profile model default, encrypted export, secret migration/export,
  project reference index, route generator, background scan, USB preparation, new SD root or second
  request-policy resolver. Existing model, instructions, tool-policy, SSH, Wi-Fi and optional-service
  ownership remains unchanged.

### Existing owner and consumer inventory

- `Settings.apiKey`, `Settings.apiBaseUrl` and `Settings.model` are currently scalar. `storage.cpp`
  reads/writes `assistant/api_key`, `assistant/base_url` and `assistant/model`; every ordinary Device or
  Web settings save currently rewrites the scalar pair, including unrelated Device, network and Web
  commits. Provisioning and existing Device/Web settings editors are the only credential producers, and
  the serial `APIBASEHEX` diagnostic also reaches that scalar save. The new owner must remove the pair
  from ordinary saves, move UI/diagnostic mutations to dedicated profile operations, and make
  `loadSettings` supply the resolved default tuple without adding profile vectors or retained extra
  secrets to `Settings`. Provisioning remains a dedicated commit followed by restart; Web Console close
  already reloads Device settings, while successful live Device/Web default changes reload their own hot
  tuple immediately.
- `ProjectDocument.apiProfile` is already validated as a bounded optional string, serialized, loaded,
  duplicated and preserved by project bundle import/export. No runtime request, model discovery or UI
  currently consumes it. Its non-secret bundle representation remains unchanged; only newly submitted
  assignments are constrained to blank or an existing stable profile ID.
- `resolveProjectRequestPolicy` owns model/context/output/compaction precedence only. Every Device and
  Web initial request, retry, compaction-summary request and Pending continuation currently clones global
  `Settings` and overrides only `model`; those are all consumers of the one new JIT profile resolver.
  STT, TTS, Web Search and tool-routing consumers continue to receive their existing independent fields.
- Device ownership is the existing `AiMenu`, modal selection/text-input primitives, Project Actions and
  global/project/chat model picker. The accepted modal primitives already provide bounded input and
  masked secret entry. No new top-level carousel destination or parallel input/navigation framework is
  required.
- Web ownership is the existing authenticated Settings state/commit surface, raw Project Settings save,
  `/api/models`, route guard and embedded HTML asset. Public state currently returns only whether the
  scalar key exists. P6-02 adds bounded public metadata only, stable-ID controls and single-purpose
  create/update/default/delete/create-preset/update-preset/delete-preset/apply endpoints. Every mutating
  handler personally requires the existing session plus CSRF check. NVS-only mutations do not acquire an
  SD lease; assignment and preset Apply retain the existing project-write owner and SD failure mapping.
- `saveProject` already writes project metadata then its index and rolls metadata back when the index
  mutation fails. This is the sole preset-Apply and project-assignment commit owner. Existing arbitrary
  imported profile references are not revalidated during unrelated project saves.
- The default NVS partition is shared with `assistant`, `cardmind_ssh`, `cardmind_py` and vendor Wi-Fi
  namespaces. The exact partition is 0x5000 bytes. P4's observed 1,675-byte SSH-key success and
  16,384-byte replacement rejection prove prior failure preservation only; they are not treated as a
  current free-capacity measurement.

### Pinned vendor semantics and fixed storage design

The exact installed source is M5Stack ESP32 package 3.2.1 with ESP-IDF release-v5.4
`idf-release_v5.4-2f7dcd86-v1`. `Preferences.cpp` commits every `putString`, `putBytes`, scalar put and
`remove` but collapses NVS errors to zero/false; it is therefore not the profile-store write API.
The new owner uses raw ESP-IDF NVS calls so the exact result survives. The pinned `nvs.h` limits
keys/namespaces to 15 characters, defines one 32-byte entry as the allocation unit, charges blobs two
overhead entries plus one per 32 bytes, exposes aggregate `nvs_get_stats.available_entries`, and requires
at least one available entry even for a scalar update. Its documented `ESP_ERR_NVS_REMOVE_FAILED` means
the requested value may already have been written and the interrupted update completes after NVS
reinitialization; code must not report old authority or delete either possible winner on that result. One
NVS page contains 126 entries. A native single-key update recovers as either the old or new valid value;
multi-key profile authority still needs an explicit generation selector.

The smallest design uses namespace `cardmind_api` and no stored count. Three profile selectors point to
fixed A/B generations. A profile generation contains a metadata blob and a separate secret blob;
list/state reads only the selected metadata. Metadata carries version, stable ID, authority revision,
exact secret length, name and base URL. The matching secret record carries version, authority revision,
exact length and the key. A request loads only the selected generation and rejects a revision/length
mismatch. Each of the six preset slots is instead one self-contained versioned native NVS blob with ID,
name, model and output: it has no selector, second generation or orphan protocol because no cross-key
invariant or persisted reference requires one. The schema marker is written last during first migration;
the default stable ID is a separate verified string. Any authoritative wrong NVS type, selector, version,
length, duplicate ID, default mismatch or record validation failure is an explicit storage error with no
legacy/default substitution. Typed results distinguish validation, not-found/conflict, capacity, corrupt,
definite storage failure, `LegacyRetained`, committed-with-cleanup-failure and `AuthorityUncertain` rather
than collapsing an NVS result to false. Before creating a missing namespace or issuing any provider NVS
mutation, the owner computes that operation's exact additional entry requirement from the encoded record
sizes, including its authority record, and reads aggregate `available_entries`. A lower measured value
returns `Capacity` before the first provider write. A later vendor write error is never relabeled as that
preflight outcome.

At maximum values, profile metadata is at most 253 bytes (10 NVS entries), its secret record is at most
519 bytes (19 entries), and the selector consumes one entry: 30 entries per active profile, 90 for three.
A single preset blob is at most 191 bytes (8 entries), 48 for six. The 16-character default string uses
two entries; schema and namespace use one each. The maximum active footprint is therefore 142 entries. A
maximum profile COW write needs at most 30 additional available entries before old-generation cleanup,
for a 172-entry active-plus-peak bound; the smaller native preset replacement needs at most eight new
entries. `available_entries`, not nominal partition bytes or `free_entries`, is the runtime gate;
ESP-IDF's reserved GC space is already excluded from `available_entries`. Real measurements must record
partition total/used/available plus this namespace's used entries before fixtures, at maximum shape, at
profile/preset replacement or rejection, and after cleanup.

### Legal persistence transitions and crash windows

1. **Singleton migration:** only an absent schema key leaves legacy `assistant/api_key` and `base_url`
   authoritative. The new default secret, metadata and selector are written/read back, the default ID is
   written/read back, and schema version 1 is issued last. Deterministic validation or exact aggregate
   capacity preflight rejection returns `LegacyRetained`, preserves the unchanged singleton and performs
   no provider NVS write, including namespace creation. An uncertain
   candidate/selector/default write aborts before the marker, preserves legacy authority and defers all
   candidate cleanup until a later boot has completed NVS initialization. An uncertain schema write
   returns `AuthorityUncertain`, permits no provider HTTP or mutation retry in that boot, and leaves both
   legacy and new records untouched. On the next normal boot, an absent marker selects legacy and permits
   exact partial-key cleanup, a valid marker selects and validates the new collection, and a present
   wrong-type/version marker hard-fails. Only a verified valid marker makes the new collection
   authoritative; legacy keys are then ignored, removed and verified absent. Interrupted legacy cleanup
   leaves harmless duplicates for the next exact boot cleanup and never reopens legacy authority.
2. **Profile create/update:** the empty/inactive generation is removed and verified absent before staging
   its complete secret and metadata. The selector is not issued until both target records read back and
   validate. A definite target-write failure leaves the old selector authoritative; a target
   `ESP_ERR_NVS_REMOVE_FAILED` also cannot change that selector but leaves the possible inactive orphan
   untouched until boot initialization resolves it. A verified selector commit makes the new generation
   authoritative and only then permits old-generation cleanup. Selector `ESP_ERR_NVS_NOT_ENOUGH_SPACE`
   leaves the old selector; `ESP_ERR_NVS_REMOVE_FAILED` or any post-issue outcome that cannot prove
   noncommit returns `AuthorityUncertain`, leaves both generations untouched and is resolved from the
   actual selector after the next normal NVS initialization. A later cleanup failure is
   committed-with-cleanup-failure; it is never presented as if the old value won.
3. **Default switch:** the requested existing complete stable ID is checked before the default-string
   update. A definite pre-issue/capacity rejection preserves the old default; a verified commit selects
   the new ID and refreshes the caller's hot default tuple. An uncertain write returns
   `AuthorityUncertain`, performs no cleanup or hot-tuple claim, and boot resolves the actual old/new ID.
   Profile records do not move or copy.
4. **Profile delete:** deleting the current default is rejected before mutation. Removing and verifying a
   non-default profile selector is the authority transition. Verified removal makes the stable ID
   unavailable before exact generation cleanup; definite pre-issue rejection preserves it. Uncertain
   erase returns `AuthorityUncertain`, leaves both generations untouched and lets boot decide from the
   actual selector whether the profile exists. Project references are deliberately untouched.
5. **Preset mutation:** create/update is one native NVS blob write. Verified commit/readback selects the
   new valid blob; `ESP_ERR_NVS_NOT_ENOUGH_SPACE` preserves the old blob; `ESP_ERR_NVS_REMOVE_FAILED` or
   another unresolved post-issue outcome returns `AuthorityUncertain` and boot validates whichever old or
   new value NVS retained. Delete uses the same verified/uncertain distinction for its one key. There is
   no selector or generation cleanup. Apply never changes the preset and uses the existing SD project
   transaction; an SD/full/index failure preserves the project's old model/output.
6. **Settings authority and hot copies:** ordinary `saveSettings` never changes provider credentials,
   regardless of stale scalar values in its argument. Dedicated provisioning, profile/default and
   diagnostic operations are the only producers, but `APIBASEHEX` is accepted only in `Ready`; every
   other initialization state returns a typed local rejection before NVS access, leaving the
   legacy-kind/boot-generation Pending identity unchanged. After a verified Device or Web change to the
   active default, that surface reloads the committed default tuple; failed commits retain its previous
   tuple. Web Console close retains its existing full `loadSettings` refresh and provisioning restarts so
   boot performs the refresh. Non-default edits/deletes cause no hot-default churn. An uncertain store
   state makes JIT resolution fail locally even if an old tuple remains in RAM.
7. **Request/Pending:** initial request and model discovery resolve the current typed authority before
   HTTP. Pending continuation loads the owning project again, resolves its current authority once,
   compares profile ID/revision or the legacy-kind/boot-generation identity with the RAM capture, and only
   then constructs the request `Settings` copy. A successful same-boot legacy migration, relevant default
   switch, assignment, deletion or authority edit stales the continuation. Reboot already removes RAM-only
   continuation context; no durable Pending secret, secret-derived identity or replay path is added.

### Frozen proportional proof matrix

| Contract / forbidden effect | Smallest evidence before closure |
| --- | --- |
| Validation, IDs, record codecs, count and length boundaries | Host tests call production validation/codec for exact min/max, over-limit, malformed type/version/length/revision, duplicate/default and preset-output cases. |
| Migration, schema and transition authority | Host outcome tests preserve exact `esp_err_t` classification and the focused final-core serial selector verifies absent-schema migration, `LegacyRetained` validation/capacity preflight rejection with unchanged singleton and zero provider writes, secret-free warning/management reporting, valid-schema boot authority, present-invalid hard failure and planned single reboot resolution from deliberately prepared old/new selector states. `ESP_ERR_NVS_REMOVE_FAILED` classification is `AuthorityUncertain`, with no cleanup, retry or HTTP in that boot; it is not deliberately provoked on Device. Output contains only booleans/counts/stats, never secret bytes, values, paths or lengths. Failure of normal readiness after the planned reboot terminates this path without any reset/recovery escalation. |
| Measured 3/6 capacity and full-storage behavior | On the same upload, collision-checked exact-owned maximum-shape synthetic profiles/presets plus bounded filler prove the 142-entry active shape and drive aggregate `available_entries` below the exact computed profile-COW need and separately below the exact native preset-replacement need. Each attempt must return `Capacity` before any provider NVS write and preserve prior authority; `AuthorityUncertain` fails this oracle. Record aggregate and namespace entry counts before/max/rejection, then remove and verify all filler plus recovered aggregate capacity before the separate planned reboot-persistence step. No extra build/upload exists only for statistics. |
| Default, explicit missing reference and Pending binding | Host codec plus focused Device/Web runtime checks prove blank inheritance, exact explicit selection, default-delete rejection, allowed non-default deletion, local unavailable error before HTTP, and stale continuation after assignment/ID/authority changes. A `LegacyRetained` request can become Pending using only legacy-kind/boot-generation; unchanged legacy continues, while successful same-boot migration stales it. No project scan/rewrite, secret capture or secret-derived hash occurs. |
| Settings producer isolation and hot tuple | Host/integration checks save unrelated Device/network/Web settings with deliberately stale scalar credentials and prove profile/legacy authority is byte-for-byte unchanged. Focused Device/Web checks prove a verified active-default edit/switch refreshes the local hot tuple, non-default mutation does not, ordinary failure retains it, and `AuthorityUncertain` prevents HTTP rather than trusting RAM. Provisioning restart is covered separately; `APIBASEHEX` proves one `Ready` update and pre-write typed rejection in `Unconfigured`, `LegacyRetained` and `AuthorityUncertain`. |
| Preset inert selection and Apply | Host validation plus real `saveProject` integration proves selection/New has no write, success copies only model/output, and injected existing SD-write failure preserves the prior project bytes/state. |
| Web contract and secret non-disclosure | Static UI/route tests prove only stable IDs, route/control reachability and generated-asset consistency. In the existing focused authenticated HTTP lifecycle, unauthenticated and bad-CSRF profile/preset mutations reject with state unchanged; create without a key rejects; blank-key edit preserves exactly the selected profile's key; and a nonce secret appears only in its exact write-only mutation form body, never in local request/response JSON, URL, local headers, state, serial output or later responses. The expected outbound provider `Authorization` header is excluded from this absence oracle. The same real hardware lifecycle exercises CRUD/default/delete/assignment/preset Apply and exact cleanup while one Web Console serial owner remains active until HTTP ends; no new journey framework or source snapshot is added. |
| Provider consumer completeness | A read-only caller inventory names every Device and Web initial request, retry, compaction-summary request, Pending continuation, global discovery and project/chat/preset discovery call site and verifies each reaches the single JIT resolver instead of retaining the global tuple. Focused real request-path evidence executes one inherited-default project and one distinct explicit-profile project through that production resolver, observes only an expected-profile boolean plus provider result, and proves no silent default substitution. |
| Device parity and resources | Source reachability checks plus focused real-Device selector/render observations cover AI profile/preset actions, Project assignment and global versus project discovery. Record free heap, largest block, stack margin and bounded operation/render latency against the 70-KiB floor. Full P6 visual redesign remains P6-06. |
| Exact-owned cleanup | The fixture ledger restores the original default by stable ID, removes only nonce-owned profiles, presets and filler, verifies them absent, verifies aggregate capacity recovery, and internally confirms unchanged API credentials and Wi-Fi configuration without emitting them. Cleanup failure fails the suite. |

### Expected row-owned write set and pre-edit gate

The expected production boundary is one cohesive `src/provider_profiles.h/.cpp` owner; integration in
`storage.cpp/.h`, `provisioning.cpp/.h`, `CardputerAssistant.ino`, `DeviceMenus.ino`, `FileTools.ino`,
`NetworkSetup.ino`, a small `ProviderProfiles.ino` modal workflow, `KeyboardNavigation.ino`,
`VoiceAndSpeech.ino`, `web_console.cpp/.h`, `web_console_routes.h/.cpp`,
`web_console_state.h/.cpp`, and the Web asset plus its generated embedded header. The proportional
retained proof boundary is `host_tests.cpp`, its existing CI
compile list in `.github/workflows/firmware.yml`, Web static tests, the focused hardware Web runner, the
existing serial regression runner and one focused `SerialDiagnostics.ino` selector. The workflow change is
exactly one source-link entry for `provider_profiles.cpp`; it adds no job, dependency, command or build
plumbing. `project_storage`, bundles, API client, tool policy, optional providers and P6-01 are unchanged
unless a concrete pre-edit reviewer blocker proves an omitted existing consumer.

The fresh independent persistent/security-sensitive pre-edit reviewer returned `STOP` by
2026-09-10T12:55:34+03:00 against the actual sources: preset A/B machinery was unnecessary, collapsed
`ESP_ERR_NVS_REMOVE_FAILED` made the authority transitions unsafe, ordinary settings saves/hot copies had
unfrozen ownership, and `LegacyRetained` Pending/proof was incomplete. The corrected design, transitions,
capacity count and proof matrix above resolve those exact blockers. The same reviewer performed the one
permitted verification of its own corrections and returned `GO` at 2026-09-10T13:04:46+03:00 with no
remaining blocker. The package now awaits Architect's personal reconciliation and explicit production
pre-edit `GO`; until then production and test files remain frozen.

Architect returned `P6-02 PRE-EDIT STOP` at 2026-09-10T13:10:34+03:00 after personally checking that the
independent blockers were resolved. The remaining bounded corrections were: reject `APIBASEHEX` outside
`Ready`; move Web security/secret claims from static assertions to the existing real HTTP lifecycle;
require low-capacity preflight to return `Capacity` before any Device write and clean filler before the
separate reboot step; name the one workflow source-link edit; and make the complete provider caller
inventory plus inherited/explicit real resolution observable. Those corrections are now frozen above.
No further independent review is required; production/tests/build/Device remain frozen pending
Architect's focused recheck and explicit `P6-02 PRE-EDIT GO`.

Architect personally returned `P6-02 PRE-EDIT GO` at 2026-09-10T13:16:12+03:00 after checking the
corrected lines, actual producer/consumer paths and pinned ESP-IDF semantics. The accepted boundary is
exactly the locked contract, storage design, transitions, proof matrix and write set above. P6-02 remains
the sole `in_progress` row. Production edits may now begin; any responsibility/write-set growth or changed
vendor semantics freezes them again and returns to Architect.

Implementation checkpoint 2026-09-10T14:05:24+03:00: the active hypothesis was that the new raw-IDF
NVS owner preserved the frozen authority state machine while existing request callers were being rebound.
A bounded read-only code audit falsified five details inside P6-02 ownership before any build or Device
action: migration selector/default uncertainty was collapsed to `LegacyRetained`; the retained-legacy
identity used a constant rather than a boot generation; legacy cleanup could open a missing namespace
read-write before an existence probe; ready-store transport/read failures were mislabeled `Corrupt`; and
namespace measurement omitted its namespace entry. The correction keeps any uncertain authority from
HTTP until a normal boot, creates one nonzero in-memory legacy generation per store boot, probes legacy
storage read-only before cleanup, reserves `Corrupt` for proven malformed records, and reports the
namespace entry explicitly. Successful migration also preserves its committed disposition through the
post-commit inspection. This is a same-row root-cause correction within the frozen write set, not a scope
or ownership change; Web/runtime integration remains paused until the corrected boundary is checked.

Architect returned `P6-02 IMPLEMENTATION STOP` at 2026-09-10T14:42:10+03:00 and froze further
integration, tests, build and Device work after personally reconciling the current store boundary. The
single root cause was that preparation of an inactive/non-authoritative generation and cleanup after an
already committed authority switch shared one cleanup result. The bounded correction separates fresh
`Unconfigured` bootstrap from actual legacy migration; returns fresh validation, capacity, open and
staging failures in `Unconfigured` with their real typed operation result; adds one boot-local profile-
mutation latch for uncertain candidate preparation/staging and unresolved post-authority cleanup while
leaving selected-profile reads/JIT resolution usable; makes preparation removal uncommitted and keeps
post-authority cleanup `committed` with `CleanupFailed`; and requires a complete metadata-plus-secret
profile read at both checks before changing the default. The latch is initialized only with the store at
normal boot and no same-boot path clears it. The actual caller inventory also proved four necessary
existing-owner paths omitted from the original list: `provisioning.h`, `web_console.h`, `FileTools.ino`
and `NetworkSetup.ino`. Those four paths are now the only accepted write-set addition in the frozen list
above; they contain narrow signature/caller rebinding and add no responsibility. The corrected store
diff and this mapping must return to Architect before broader integration resumes.

Architect personally returned `P6-02 IMPLEMENTATION GO` at 2026-09-10T14:50:59+03:00 after inspecting
the corrected store/header, the exact four added caller/header owners and the trace mapping. The verdict
confirmed that all five STOP items are resolved in the actual source, `git diff --check` has no whitespace
error, and no route, schema, framework or unrelated responsibility was added. P6-02 integration and its
frozen proportional proof may resume in the same row; any further responsibility/write-set growth or
changed vendor semantics freezes production again.

Architect returned `P6-02 TEST-GATE STOP` at 2026-09-10T15:27:37+03:00 before any test, build or Device
run. The first Web static-test draft had crossed the frozen proportional boundary by slicing production
handler/helper source and duplicating provider-state and payload implementation fragments. That source-
snapshot draft was removed without replacement. The retained static delta is limited to stable control
IDs, required input attributes, specialized-route reachability and generated-asset equality. General-
settings provider isolation, inert selection and key-draft clearing, secret absence, authenticated/CSRF
mutation behavior, project assignment and preset Apply remain owned by the already frozen real
authenticated HTTP/Web lifecycle; production validation and codecs remain owned by host tests. Further
production or test execution stays frozen until Architect reviews this reduced proof boundary.

Architect personally returned `P6-02 TEST-GATE GO` at 2026-09-10T15:29:49+03:00 after inspecting the
reduced static-test diff and the proof-ownership correction above. The accepted retained delta contains
only stable profile/preset/project-assignment controls and required input attributes, the eight
specialized route registrations, the necessary adaptation of the pre-existing secret-draft presence
fragment, and the existing generated-asset equality check. No new handler, helper, state, payload,
ordering or literal source snapshot remains, and no replacement harness was added. Implementation and
the frozen proportional proof sequence may resume; source-snapshot assertions remain prohibited.

Architect returned `P6-02 IMPLEMENTATION STOP` at 2026-09-10T15:49:21+03:00 and froze production,
tests, build and Device work after finding that both Pending paths discarded the provider `Settings`
which had already been resolved and authority-checked before the approval/tool effect, then repeated the
provider resolution after that effect. The bounded correction carries that transient resolved value in
the Device/Web Pending-input result, moves it into the continuation after the decision, and removes the
second provider resolution and its avoidable post-effect failure window. Device no longer reloads the
project solely for that second resolution; Web retains its existing post-decision project/chat history
load but performs no second secret/NVS provider read. The one pre-effect stable-ID/revision or
legacy-kind/boot-generation comparison remains the authority gate. No durable identity, lock, retry,
transaction or proof framework was added. Tests, build and Device remain frozen pending Architect's
focused recheck of only this correction.

Architect personally returned `P6-02 IMPLEMENTATION GO` at 2026-09-10T15:53:23+03:00 after inspecting
only the corrected Device/Web Pending seams and this trace mapping. Each surface now performs exactly
one provider resolve and authority comparison before the decision/tool effect, moves the same transient
resolved `Settings` through all three decision paths, and performs no provider NVS/secret read after the
effect. Device removed its redundant project reload; Web retains only its existing history/project
reload. The focused diff has no whitespace error and adds no durable field, lock, retry, transaction or
test responsibility. The same row and its frozen proportional proof sequence may resume.

The fresh independent persistent/security-sensitive code review returned `STOP`, recorded at
2026-09-10T16:22:02+03:00, before upload or Device work. Four same-row blockers are frozen: inherited
default resolution currently converts a definite profile-storage read failure into `Corrupt` instead of
preserving the typed storage/uncertain result; the raw Project-settings completion owner can persist an
API-profile assignment without first requiring the existing personal session and CSRF check; committed
profile update/delete cleanup failures are rendered as ordinary failed mutations even though the new
authority already won; and the already frozen focused serial runner plus authenticated hardware-Web
lifecycle have not yet been implemented in their named existing harness owners. The bounded correction
will reserve `Corrupt` for proven missing/malformed default authority, reject unauthenticated raw
completion before mutation, expose committed-with-cleanup-warning while refreshing authoritative UI
state, and add only the frozen P6-02 selectors/lifecycle to `SerialDiagnostics.ino`,
`tools/device_regression.ps1` and `tools/hardware_web_e2e.mjs`/`.ps1`. Production, build and COM8 work
remain frozen until these blockers are corrected and the same reviewer performs its single permitted
blocker recheck.

Architect assigned the pre-existing focused Web-runner lifecycle defects to P6-02 at
2026-09-10T16:47:52+03:00 because P6-02 had already frozen
`tools/hardware_web_e2e.ps1`/`.mjs` as required proof owners; this does not reopen a P2/P4 product
row and leaves P6-02 as the sole `in_progress` row. The permitted correction is confined to the
existing harness files: use one fixed total serial-wait deadline; perform one initial `PING` with no
retry or pre-readiness `EXIT`; track confirmed normal readiness, readiness loss and confirmed Web
Console start; never write serial after readiness loss; request shutdown only after confirmed start
while still responsive and accept only exact `WEB_CONSOLE result=stopped`; make cleanup or shutdown
failure fail the suite rather than warn; and clear the parsed installation-credential container and
password reference immediately after login. The already frozen `p6-providers` selector/lifecycle may
be added without changing dormant legacy suites or introducing another runner/helper framework.
Only syntax/static lifecycle checks are permitted before the same independent reviewer's single
blocker recheck and Architect's focused recheck; production builds, upload and COM8 remain frozen.

Architect approved one bounded unavailable-reference compatibility correction at
2026-09-10T17:28:14+03:00 after the actual browser/backend path showed that the new renderer rejected
an arbitrary dormant/imported `ProjectDocument.apiProfile` value and the Project-settings form would
resubmit that unavailable value into the new canonical-ID assignment validator. The existing persisted
contract deliberately permits a valid UTF-8 value through 120 bytes so imports and deleted references
remain visible and fail closed until explicit reassignment. The asset-only correction therefore accepts
that exact stored boundary for display through `textContent` and omits the API-profile header when the
unchanged disabled unavailable option remains selected, causing the existing backend
`apiProfileProvided == false` path to preserve it. Explicit Inherit and a selected available stable ID
retain their current validation. This adds no storage/backend owner, codec, module or compatibility
framework and joins the already frozen unavailable-reference Web observation; the embedded asset will
be regenerated with the consolidated P6-02 correction package.

Task-clock checkpoint 2026-09-10T18:08:55+03:00: primary active work remains on the focused P6-02
harness blocker correction. Architect's new source-level evidence narrowed the current root cause to
serial timeout/write failures that did not first mark readiness lost, batch/partial-line handling that
could accept a completion before a reset in the same read, and login cleanup that ran only after a
successful authentication response. The materially corrected approach carries one serial partial buffer,
classifies the complete batch before accepting a match, marks loss before logging or cleanup, wraps each
shared Web Console start/stop write, and clears parsed credentials in `finally`. Only syntax/static
lifecycle checks follow; build, upload and COM8 remain frozen pending the same independent reviewer's
single blocker recheck and Architect's focused recheck.

Architect personally returned `P6-02 REDUCED PROOF-DESIGN GO` at
2026-09-10T18:33:39+03:00 after checking the roadmap contract and the actual
`initialize`/`inspectReadyStore` boot ordering. The product contract and fail-closed persistence behavior
are unchanged; only the Device proof is reduced to preserve live authority. No boot hook, RTC state,
automatic recovery, credential copy, extra namespace or runner framework is permitted. The existing
`SerialDiagnostics.ino` selector may create one collision-checked nonce-owned non-default profile, stage
only that fixture's inactive generation and selector, emit one exact reboot marker, and restart once.
`tools/device_regression.ps1` may permit that single boot, require the complete batch and carried partial
to be free of panic, `FATAL` and a second reset before accepting the fixed-deadline `READY`, then send the
same nonce-bound continuation exactly once. Failed readiness ends the path without `PING`, cleanup,
reset, reupload or another serial write; a remaining nonce-owned fixture is an honestly failed proof, not
completion or recovery. The original default stable ID, credentials and Wi-Fi stay untouched.

The production-codec arithmetic of 142 active and 172 active-plus-profile-COW entries remains a verified
upper bound, not a Device equality claim. Final-core evidence instead records the real baseline, every
available nonce-owned maximum-shape profile slot plus six maximum-shape presets, the exact 30-entry
profile and eight-entry preset update preflight rejections, and recovered aggregate capacity. A full
existing profile inventory is a pre-mutation capacity/precondition failure; the proof never edits a
protected profile to manufacture the theoretical count. Destructive live-schema migration replay is
also removed. Migration ordering, invalid schema and typed vendor outcomes retain production-codec and
focused source-review evidence; the real first normal migration/Ready boot is observed only when it
occurs naturally. This limitation must remain explicit and no injected migration-failure claim may be
made. The primary-active reboot-design interval was about 25 minutes from the 18:08:55 root-cause
checkpoint, so no 60-minute pivot threshold was reached. Build, upload and COM8 remain frozen pending
the original independent reviewer's single blocker recheck and Architect's focused GO.

Architect issued a focused selector `STOP` before execution at
2026-09-10T19:12:25+03:00. Source review found that the WIP proof collapsed raw candidate and selector
write uncertainty into booleans and could then mutate NVS during cleanup; its 256-byte filler could not
reliably cross the eight-entry production preflight; and prefix-only matching could delete a profile
before complete nonce-owned identity was established. No build, upload, COM8 command or Device mutation
had run. Production remains frozen.

The accumulated primary-active proof-correction interval conservatively reached the 60-minute pivot
boundary across the 18:08:55 through 19:12:25 checkpoints. The prior raw-generation replay approach is
therefore stopped rather than extended with more diagnostic transaction machinery. The materially
smaller proposed proof keeps the measured 30/8 capacity cases but uses one bounded sequence of
collision-checked one-entry nonce filler keys and the existing public production write-disposition
classifiers; any `outcomeUnknown` emits one typed non-secret failure and permits no later mutation. For
reboot persistence it creates one exact nonce-owned non-default profile through the production store,
updates it through the production store, restarts once, and binds name, stable ID, expected maximum-shape
authority data, default ID and reset reason before exact-owned deletion. It drops raw inactive-generation
and selector injection plus the Device `generation_cleanup` claim; unchanged crash ordering remains
covered only by production-codec host tests and focused source review. Any pre-existing nonce prefix is
a no-mutation collision. This pivot requires Architect approval before further proof edits.

Architect returned `P6-02 PIVOT GO` at 2026-09-10T19:20:10+03:00 for proof implementation only; this is
not build, Device, execution, closure or publication approval. The complete visible Phase 6 plan was
restored with P6-02 as its sole `in_progress` row before resuming edits. The accepted proof deletes all
raw profile-key discovery, inactive-generation staging and selector flipping. It uses only the production
store's create, update, resolve and delete operations for one nonce-owned non-default profile, and reports
physical `persistence=pass` rather than `generation_cleanup`. The row's new COW/crash semantics retain
source, codec and typed error-classification evidence with the explicit limitation that no injected-crash
runtime claim is made.

The two existing serial owners receive separate single-purpose selectors: `P6PROVIDERTEST<nonce>` always
begins a fresh run and rejects any pre-existing matching A/B nonce without mutation;
`P6PROVIDERFINISH<nonce>` is sent exactly once only after the runner observes the planned marker, exact
normal software `BOOT` and fixed-deadline `READY`. Finish must bind one unique exact B name, stable ID,
maximum-shape base/key, revision, non-default state, original default suffix and software reset before
deletion. Fillers are one-entry scalar nonce-owned keys whose required count is bounded from measured NVS
availability and collision-checked before mutation. Existing public write-disposition classifiers and
typed results govern every raw filler set/commit/verify/cleanup; any unknown outcome emits one non-secret
typed failure and permits no later mutation, reboot or cleanup. Definite failures may clean only exact-owned
fixtures. The frozen proof write set remains `SerialDiagnostics.ino`, `tools/device_regression.ps1` and
this trace update; build, upload and COM8 remain frozen pending the original code reviewer's single recheck
and Architect's focused execution GO.

Static correction checkpoint 2026-09-10T20:05:53+03:00: the accepted pivot is implemented without the
removed raw namespace/key discovery, inactive-generation staging or selector mutation. The focused
firmware review removed the final unused raw-namespace symbol, made exact-owned fixture cleanup stop only
on an unknown outcome while continuing safe cleanup after definite failures, and made reboot-stage cleanup
failures and resource-oracle mismatches report their own typed non-secret failure instead of masking them.
A bounded independent runner audit then found three same-owner lifecycle defects before execution: shared
readiness classification omitted `FATAL`, Web serial framing trimmed surrounding whitespace before exact
marker comparison, and credential URL/password validation could fail before the clearing `finally` block.
The corrected runners classify `FATAL` in complete and carried data, remove only a trailing CR, and put
credential parsing, validation and login inside one unconditional clearing boundary.

Observed device-free evidence is: both PowerShell files parse with zero errors; `node --check` passes for
the hardware Web runner; `WEB_CONSOLE_UI_TEST result=pass`; a disposable invocation of the production
PowerShell parser accepts the exact `persistence=pass` envelope and rejects both the removed
`generation_cleanup` field and whitespace-padded final output; and `git diff --check` reports no whitespace
error (only the repository's existing line-ending warnings). No build, upload, COM8, HTTP or browser
mutation ran. The corrected blocker package now awaits the original independent code reviewer's single
recheck; Architect execution approval remains a separate later gate.

The original independent P6-02 code reviewer completed its single blocker recheck at
2026-09-10T20:26:41+03:00 and returned exact `GO` with no remaining blocker. The separate bounded runner
reviewer also returned `GO` after verifying only its three corrected lifecycle findings and repeating the
two PowerShell parser checks plus `node --check`. This is review evidence for the frozen correction, not
execution or closure approval; build, upload, COM8 and HTTP remain stopped pending Architect's focused
execution verdict.

Architect personally returned exact `P6-02 EXECUTION GO` at 2026-09-10T20:31:58+03:00 after inspecting
the actual corrected worktree, canonical matrix and visible plan, independent review verdicts, static
evidence and whitespace check. The reviewed correction hashes were
`SerialDiagnostics.ino` `D8CF2A7C8EE03C0589B8D227555350D36E171212C4F0E652A327CF22B7E660FA`,
`device_regression.ps1` `133F1C8945E646EAB0575398D7B8448932F30D842CB540753788F93CDC8662E4`,
`hardware_web_e2e.ps1` `FC207BA97E95D5ECB205F94D6E70E541E76BBC17C793110171138624794FD01D`
and `hardware_web_e2e.mjs` `5D07552CF60A8E2481D1FFCDC24E8B3141E0526F854CEF6C489AC6A3655420A0`.
The complete canonical visible plan was restored again before execution with P6-02 as its sole
`in_progress` row. Approved execution is limited to pin validation, cheap strict host/static checks, one
exact pinned compile and options inspection, one upload, then only the frozen focused serial and
authenticated hardware-Web `p6-providers` paths. This is not closure, completion, staging, commit or
publication approval. Any unexpected readiness loss ends that path without another probe, reset,
reupload or recovery; the no-injected-crash runtime limitation and codec-derived-only 142/172 bounds
remain explicit.

Execution evidence checkpoint 2026-09-10T20:42:13+03:00: the approved bounded execution completed
without expanding the proof matrix. The exact library-pin check passed. Both PowerShell runners parsed,
`node --check tools/hardware_web_e2e.mjs` passed, `WEB_CONSOLE_UI_TEST result=pass`, the strict focused
serial parser retained its exact positive and two negative outcomes, and `git diff --check` reported no
whitespace error. The first disposable host-test invocation failed before compilation because its Bash
output-path variable arrived empty; no ELF was created. Replacing only that invocation boundary with an
exact validated `/tmp/cardmind-host-tests-p602-<timestamp>` path and trap cleanup produced
`host_tests: PASS`, and the current CI source inventory includes `provider_profiles.cpp`.

One exact pinned compile then succeeded with FQBN
`m5stack:esp32:m5stack_cardputer:FlashSize=8M,PartitionScheme=custom`: the sketch used 3,622,042 bytes
(21%) of program storage and 65,876 bytes (20%) of global-variable storage, leaving 261,804 bytes for
local variables. Inspection of generated `build/p3-phase/build.options.json` proved the exact FQBN,
exactly one resolved M5Stack hardware core, and version `3.2.1`. The single approved COM8 upload then
succeeded, with every written data hash verified. Its final `Hard resetting with RTC WDT` line was the
uploader's normal completion step, not a later readiness probe or recovery action; no second upload,
reset, probe or recovery action ran.

The sole focused serial run, retained in `artifacts/p6-02-providers-device.log`, ran from
2026-09-10T20:39:58.6858175+03:00 through 20:40:18.3905031+03:00 and returned
`CARDMIND_REGRESSION result=pass cases=1`. Its nonce-bound measured envelope observed one pre-existing
profile, two exact-owned profiles, the three-profile maximum, six presets, NVS total 630, available
entries 192 before and after exact cleanup, and namespace count 14 before and after cleanup. The
profile-capacity rejection occurred at 29 available entries and recovered to 84; the preset-capacity
rejection occurred at 7 and recovered to 84. The measured boundary used 107 ms for the operation and
20 ms to render, with free heap 119,884 before and 113,512 after, largest block 58,356 before and 47,092
after, and 7,300 bytes of free stack. The planned reboot produced exactly one
`BOOT firmware=1.12.1 reset_reason=3`, normal startup, then exact `READY`; the nonce-bound finish returned
`reboot=pass persistence=pass resolver=pass default=pass cleanup=pass`, with free heap 116,204, largest
block 54,260 and free stack 7,816. No unexpected readiness loss occurred.

The sole focused authenticated hardware-Web run, retained in `artifacts/p6-02-providers-web.log`, kept
one serial owner from `WEB_CONSOLE result=ready` through exact `WEB_CONSOLE result=stopped` and ran from
2026-09-10T20:41:34.2097613+03:00 through 20:42:13.0384197+03:00. Its one JSON evidence envelope and
final runner result both passed authentication/CSRF rejection, missing-key nonmutation, profile CRUD and
public state, default/project binding, connector-failure outcomes, unrelated settings isolation, preset
CRUD/Apply, unavailable-reference failure, secret non-disclosure and exact cleanup. Profile creation took
35 ms and preset Apply 1,112 ms. Resource observations changed from free heap 97,556, largest block
34,804 and free stack 5,720 to 94,572, 31,732 and 4,936 respectively, remaining above the frozen gates.
The exact-owned ledger was verified complete and removed; the runner-retained Node stdout artifact is
569 bytes, stderr is empty, and neither is row-owned commit content. The runtime secret oracle passed
before the credential variable was cleared. API credentials and Wi-Fi configuration were not changed.

These observations prove the frozen normal-write, deterministic-capacity, physical reboot-persistence,
real authenticated Web lifecycle, resource and cleanup cases. They do not create an injected-crash
runtime claim: COW/crash ordering remains covered only by the production codec/host boundary and focused
source review, while the 142-entry active and 172-entry active-plus-maximum-profile-COW bounds remain
codec-derived rather than physical capacity counts. P6-02 remains the sole `in_progress` row pending
proof audit and Architect's personal closure review; nothing is staged, committed or pushed.

Closure-reconciliation STOP checkpoint 2026-09-10T21:12:04+03:00: primary line-by-line review found
that Web preset Apply could return HTTP 500 after `saveProject` had already made the new model/output
authoritative, and that provisioning could collapse a committed provider cleanup warning into HTTP 400
without scheduling its required restart. A fresh proof red-team independently returned `STOP` on the
preset path and also found three proof-owner defects: the fixed ledger `.node.tmp` path was opened with
truncation without collision or failure cleanup, Node stdout/stderr captures remained after the run, and
the nonce probe secret was cleared before Console shutdown so later serial output escaped the final
absence oracle. A separate provisioning review already dispatched before the consolidated verdict
independently returned `STOP` on the same committed/no-restart transition. The proof red-team otherwise
accepted the retained Device/Web envelopes, resources, planned reboot, Console lifecycle and fixture
cleanup. The inaccurate wording in the preceding checkpoint was corrected: 142 is the codec-derived
active NVS-entry bound and 172 is active plus one maximum-profile COW, not profile/preset byte counts.

Architect returned `P6-02 CLOSURE STOP` for this one same-row blocker batch. The clarified contract is
that load or save failure before `saveProject` preserves old project authority, while any failure after
a verified commit is explicitly reported as applied-with-refresh-warning and never as rollback. A
committed Apply must immediately update the Device/Web hot model and output values used by the next
request, advance the Web project/chat observation revisions at that authority point, and then attempt
canonical project and project-list refresh once. Neither surface may reproduce `saveProject`'s stored
revision/timestamp arithmetic. The Web asset must preserve the committed response and render a later
`refreshChat` failure as an applied-with-refresh-warning result.

The provisioning correction removes the new one-caller wrapper instead of adding another result type.
Its sole caller retains the typed provider result: an uncommitted or authority-uncertain provider failure
stops before ordinary settings and schedules no restart; successful or committed-with-cleanup-warning
provider authority calls ordinary `saveSettings` exactly once. A later ordinary-settings failure reports
the partial result without claiming all settings saved or scheduling a recovery restart. When ordinary
settings verify, the caller updates its hot settings, returns a visible saved-with-cleanup-warning when
needed, and schedules the existing five-second restart exactly once. It performs no provider retry,
cleanup retry, compensation or cross-store transaction.

The proof-owner correction reserves and collision-checks the exact main ledger, fixed `.node.tmp` and
Node capture sidecars before Device mutation. Node creates the temporary ledger exclusively and removes
only a temp this invocation created when its write/rename fails; the wrapper removes and verifies its
reserved temp and captures on every outcome. The probe secret remains live through exact Console shutdown
and all final serial output, the absence oracle scans the finalized log and captures, and only then is
the probe cleared and the captures removed. The current failed-proof residue is exactly one 569-byte
stdout capture and one empty stderr capture; the main ledger and `.node.tmp` are absent. They remain
untouched until the correction is approved.

The proposed correction write set is limited to `ProviderProfiles.ino`, `src/web_console.cpp`,
`src/provisioning.cpp`, removal of the one-caller helper from `src/storage.cpp/.h`, the Web asset and
generated header, `tools/hardware_web_e2e.mjs/.ps1`, and this trace. The frozen proof delta is an exact
changed-branch review without physical failure injection or another harness; PowerShell parsing,
`node --check`, asset consistency/UI stable checks, focused host tests and whitespace checks; then only
after independent blocker rechecks and Architect execution GO, one exact compile/options check and at
most one upload plus one authenticated hardware-Web `p6-providers` run. Prior NVS capacity, reboot,
serial CRUD, cleanup and resource evidence remains valid; the focused serial provider run is not
repeated. Production and runner edits remain frozen pending Architect's verdict on this correction
design/proof delta.

Architect returned `P6-02 CORRECTION DESIGN GO` for the consolidated three-part delta. One exact
downstream amendment is frozen inside the existing Web owner: because a post-Apply canonical reload
failure deliberately leaves only the committed model/output in the hot project while its stored summary
revision remains unknown, raw Project Settings completion must freshly `loadProject` before it reads,
mutates or saves any project field. A read failure rejects before any write; a success uses that canonical
document for `saveProject`. This prevents a later stale cached summary revision from becoming a save
input without duplicating `saveProject` revision/timestamp arithmetic, adding a flag or changing the
storage owner. The complete canonical visible plan was restored with P6-02 as its sole `in_progress`
row. Production correction is now authorized only inside the frozen write set. Cheap syntax, asset,
host and whitespace checks plus the two existing reviewers' one blocker recheck are authorized; compile,
upload and the one replacement hardware-Web run remain frozen pending a separate Architect execution
verdict. The focused serial provider run must not be repeated.

The user's latest explicit clarification is to preserve what has already been written. It supersedes the
brief proof-pruning request: no production, test, selector, runner, ledger or helper is removed, replaced
or simplified merely to reduce complexity. The approved correction remains an in-place repair of only
the concrete Apply, canonical Project-save input, provisioning outcome, temp/capture ownership and final
secret-scan defects above. No new test case, runner, ledger protocol, framework or cleanup refactor is
added. Cheap checks remain authorized after the correction; expensive execution remains separately
gated, and P6-02 remains the sole `in_progress` row.

Correction evidence checkpoint 2026-09-10T21:39:11+03:00: the in-place correction preserves all
existing production, helper, selector, test and ledger surfaces. Device preset Apply updates the hot
model/output immediately after the authoritative Project save and retains its existing committed-warning
reload branch. Web preset Apply updates the hot model/output and Project/chat observation revisions at
that same commit point; canonical reload and Project-list refresh failures are accumulated into an HTTP
200 committed warning. The existing WebUI requires `committed=true`, preserves the backend warning and
reports a later chat refresh failure as an applied-with-refresh-warning outcome. Raw Project Settings now
loads the canonical active Project before reading inherited fields or constructing its sole save input,
and a failed load returns before any write.

The retained `saveProvisionedSettings` helper now returns the typed provider result. It advances to the
ordinary settings save only for provider success or exactly `CleanupFailed + committed`; every
`AuthorityUncertain` result returns before that save even when a prior schema write set its `committed`
field. Ordinary settings are saved exactly once on the allowed branches. Their failure returns a
distinct partial-storage error with no restart; their success preserves the committed cleanup warning so
the existing provisioning caller updates hot settings, sends a truthful HTTP 200 warning and schedules
the existing five-second restart once. No provider retry, cleanup retry, compensation or new result type
was added.

The existing hardware-Web runner now collision-checks the exact P6 ledger, fixed Node temporary ledger
and both capture paths before Device mutation. The Node ledger writer uses exclusive temporary creation,
closes and removes only a temporary file created by that invocation on failure, and leaves a cleanup
failure explicit. The wrapper retains an unexpected remaining temporary ledger as failure evidence,
keeps the derived probe live through exact Console shutdown, scans the finalized log and reserved
captures only after serial shutdown, then clears the probe and removes and verifies its reserved capture
files. A pre-existing collision is never marked owned or removed. The previously observed residue is
unchanged while execution remains gated: the main ledger and fixed temporary ledger are absent, while
the exact stdout/stderr captures remain at 569 and 0 bytes respectively.

The regenerated Web asset measured 140,513 source bytes and 35,085 gzip bytes; a second generation was
byte-identical with SHA-256
`4E6AC62C9994613CEBD7963C06D55724B6398FCE41E32442997102D614F538EC`. Both PowerShell runners parsed,
`node --check tools/hardware_web_e2e.mjs` passed, `WEB_CONSOLE_UI_TEST result=pass`, and
`git diff --check` reported no whitespace error. The first correction host invocation again exposed the
PowerShell-to-WSL empty-variable boundary and failed before compilation with no ELF created. The
materially different literal, collision-checked `/tmp/cardmind-host-tests-p602-correction-20260910-232100`
invocation then returned `host_tests: PASS` and verified removal of its exact ELF.

The existing proof red-team reviewer performed its one blocker recheck against the actual corrected
Apply, WebUI, runner and 142/172 wording and returned explicit `GO`. The existing provisioning-order
reviewer used its recheck to identify a reachable schema-committed `AuthorityUncertain` path that the
first gate had admitted to ordinary settings. That concrete STOP was resolved by restricting the helper
gate to provider success or exactly committed cleanup failure; the corrected source and subsequent
whitespace/staging check are clean. No further reviewer loop, build, upload, serial run, HTTP run or
Device action has occurred. P6-02 remains `in_progress` pending Architect's separate execution verdict.

Architect personally inspected the final provisioning gate and sole consumer, verified all ten reported
worktree hashes and the exact artifact inventory, and returned `P6-02 CORRECTION EXECUTION GO`. The full
canonical visible plan was restored again before execution with P6-02 as its sole `in_progress` row. The
approved execution remained limited to exact old-capture cleanup, one pinned compile and options gate,
at most one upload and exactly one replacement authenticated hardware-Web `p6-providers` run. It did not
authorize closure, completion, staging, commit or publication.

Before execution, the two previously retained exact-owned captures were resolved to absolute paths under
this repository, required to remain exactly 569 and 0 bytes, removed individually and verified absent.
The main ledger and fixed Node temporary ledger were already absent. These disposable captures are not
recoverable, and no canonical log, configuration or Device state was removed by that cleanup.

The sole corrected pinned compile succeeded with exact FQBN
`m5stack:esp32:m5stack_cardputer:FlashSize=8M,PartitionScheme=custom`. The sketch uses 3,623,546 bytes
(21%) of program storage and 65,876 bytes (20%) of global-variable storage, leaving 261,804 bytes for
local variables. `build/p3-phase/build.options.json` is 1,736 bytes with SHA-256
`20BA11EE73700A2D4A591C7C8DA0516C89E807BF0E66D8257ED88E8CC834C998`; its FQBN matches exactly and its
two hardware-folder references resolve to one unique
`toolchain/data/packages/m5stack/hardware/esp32/3.2.1` directory, with no other M5Stack core. The uploaded
application binary is 3,623,728 bytes with SHA-256
`3AF818C62A976807E4F8419DC79FFDF898323869C058F38652AAABC5841A3A06`; the ELF is 45,881,836 bytes with
SHA-256 `D69D250ECBA3A2CD8A54448DAE92232EA45D9E824113853E8AEFFE9DB6C41FC8`.

The single permitted COM8 upload completed successfully with each written data hash verified. Its final
`Hard resetting with RTC WDT` was the uploader's normal completion action. No later upload, reset,
separate readiness probe, recovery step or focused serial-provider run occurred.

The replacement authenticated hardware-Web run in `artifacts/p6-02-providers-web.log` ran from
2026-09-10T18:49:00.0380628Z through 18:49:39.3558279Z. The retained 1,366-byte log has SHA-256
`580606C3657D292CA167686398D7276F939974B58EA8B47EDF4F1DFC36D33D43` and contains exactly one normal
`WEB_CONSOLE result=ready`, one P6 provider result envelope, one exact
`WEB_CONSOLE result=stopped` and one final pass. Authentication/CSRF, missing-key non-mutation,
profile CRUD/public state, default/Project state, connector failures, Settings-provider isolation,
preset CRUD/Apply, unavailable references, secret non-disclosure and cleanup all returned `pass`.
Profile creation measured 35 ms and preset Apply 1,147 ms. Same-run resources moved from
97,572/31,732/5,704 bytes free-heap/largest-block/stack-margin to 94,740/31,732/4,936 bytes: a 2,832-byte
free-heap reduction, no largest-block loss and a 768-byte stack-margin reduction, all inside the frozen
floor/loss limits.

Final read-only reconciliation found no provider ledger, fixed temporary ledger, stdout capture or
stderr capture. The runner's final generated-secret scan and exact-owned cleanup therefore completed
before its pass. The nine reviewed production/Web/runner hashes were unchanged by execution. An initial
external log checker expected the console-only `suite=` wording in the retained final line and rejected
the otherwise correct log; inspection assigned that to the checker, whose read-only pattern was changed
to the runner's actual retained `completed=` contract and then passed. No product, test, runner or
evidence log was changed for that oracle correction. Prior accepted serial NVS-capacity, CRUD, reboot,
cleanup and resource evidence remains applicable with its explicit no-injected-crash and codec-derived
142/172 limitations. P6-02 remains `in_progress` pending Architect's personal closure review.

Architect personally completed the mandatory review of the actual row-owned diff, producer/consumer
paths, vendor semantics, retained tests, raw compile/upload and runtime evidence, cleanup, resources and
residual risk and returned explicit `P6-02 CLOSURE GO`. The review independently verified the exact
3.2.1 build/options and binary hashes, the replacement hardware-Web log and production-route coverage,
the prior unchanged Device capacity/reboot evidence, final secret scan, absence of every exact-owned
ledger/temp/capture, and the final provisioning `AuthorityUncertain` gate. It accepted only the stated
proportional limitations: no physical injected NVS uncertainty/crash, committed-cleanup or post-commit
refresh fault claim; no claim that the corrected Device/provisioning warning branches were physically
exercised; 142/172 remain entry upper bounds rather than measured byte counts; and full visual/soak/phase
regression remains P6-08. No further test or harness work is required for this row.

P6-02 completed at 2026-09-10T22:00:46+03:00. P6-03 remains `pending` during the required zero-active-row
publication window and may become `in_progress` only after this exact row-only commit is pushed and its
remote branch SHA is verified through the authenticated GitHub API.

P6-02 publication was verified at 2026-09-10T22:17:44+03:00. The row-only commit
`03151f07a1c2af9b434502fcf034346605f3f886` passed the local row-close check for its exact 28-path set,
was pushed without force to `feature/phase-6-ui-stable-baseline`, and the authenticated GitHub API for
`varlolwut/cardmind` resolved that branch to the same SHA with the required Author and Committer.
No GitHub Actions run is claimed for this publication. P6-03 is now the sole `in_progress` row; this
post-publication trace update is separate from the immutable P6-02 commit.

## P6-03 pre-edit inventory, design and proof freeze

P6-03 inventory began from published source
`03151f07a1c2af9b434502fcf034346605f3f886` at 2026-09-10T22:17:44+03:00. At the
2026-09-10T22:38:14+03:00 checkpoint the current root-cause hypothesis is that the shipped Web
Console conflates three independent facts: one RAM authentication token, its fixed 15-minute idle
clock, and Device `Browser session active` presentation. The expected information from the completed
read-only experiments was: source inventory would identify every authentication/presence producer and
consumer; existing-test inventory would find the smallest retained proof paths; pinned-vendor review
would determine route, connection and timer constraints; and browser-standard review would determine
which lifecycle signal can be authoritative. The results support one existing-owner correction below.
No production, test, harness, Device, build or external state has changed, and no stall checkpoint or
pivot threshold has been reached.

### Locked contract and exclusions

The binding clauses are the Phase 6 Work and Acceptance sections plus Web session/Browser presence
limit decisions in `ROADMAP.md`, this trace's scope lock and P6-03 matrix row, and the approved P6-01
session information architecture. The four persistent UX choices are exactly 15 minutes, 1 hour,
8 hours and Until reboot. The approved P6-01 artifact calls the finite value an `Idle lifetime`;
therefore finite authentication remains sliding-idle, preserving the shipped intent while removing
the shipped server/cookie inconsistency. An authenticated non-presence request resets the idle clock.
A heartbeat validates the current token and CSRF without resetting that clock. Until reboot has no
timer expiry, but explicit Lock/logout, End Console, Console teardown and reboot still invalidate it.

Presence is independent aggregate RAM state: one initialized flag and the timestamp of the last
accepted visible-tab heartbeat. `Browser connected` means that aggregate timestamp is less than
24 seconds old, never merely that an authentication token exists. While the existing synchronous
WebServer can process requests, the aggregate becomes Waiting at 24 seconds without a heartbeat.
Each visible tab sends the same bounded signal, so closing one tab cannot hide another tab that
continues to heartbeat. Losing presence never clears authentication.

While a synchronous foreground handler prevents heartbeat processing, presence is unobservable and
the Device shows its existing operation state or compact Busy rather than Connected. At handler
return the original heartbeat timestamp is evaluated without renewal or a new grace interval; only a
newly accepted visible-tab heartbeat restores Connected. `pagehide`/`sendBeacon` is optional and
cannot clear aggregate presence. Existing foreground transfers are preserved without redesign,
restriction, asynchronous ownership or a second transport.

P6-03 does not add a second server, route family, session store, microSD representation, background
service, PWA/service worker, Web framework, reconnect/draft subsystem, diagnostic dashboard, retry or
recovery framework, cookie-parser/security audit, Python/SSH redesign, general UI rewrite, or future
USB work. The current substring cookie parser is retained for the Phase 9 security audit. Existing
code, tests and harnesses remain in place; this row may only make the in-place additions listed in the
frozen write set.

### Complete current-owner inventory

- `src/storage.cpp` owns the installation password in protected NVS and the single global `Settings`
  load/save path. `src/app_types.h` has no session-lifetime field today. The lifetime choice belongs in
  this existing protected-NVS settings owner; token, CSRF and tab presence remain RAM-only.
- `src/web_console.cpp` owns the one global session token/CSRF pair, login throttling, idle timestamp,
  login/session/logout handlers, authenticated/CSRF guards, Console loop, Device-screen render and
  complete Console teardown. Its current authenticated guard both validates and touches the idle
  timestamp, so using it unchanged for heartbeat would make finite authentication unbounded.
- `src/web_console_routes.h/.cpp` owns the complete route table and collected request headers.
  `/api/session` currently has only GET. The existing pinned WebServer permits distinct GET and POST
  handlers for the same URI, so POST can own presence without a new route family.
- Every authenticated read and mutation in `src/web_console.cpp`, including raw request start,
  storage guard, prompt/Pending, Project/Chat, provider/preset, Settings, diagnostics, Python,
  SSH/SFTP, QR and file paths, consumes the shared authentication or CSRF guards. They remain the one
  activity owner. Presence POST alone uses the new non-touching authentication/CSRF guard.
- `assets/web_console.html` owns tab-local CSRF bootstrap and the common request wrapper. It already
  owns `visibilitychange`, bounded timers and visible-only SSH polling, but has no presence
  heartbeat. Browser authentication remains the shared HttpOnly cookie.
- `src/web_console_state.cpp` owns public Settings JSON. The existing Settings form and its one
  `/api/settings` save action own the Web lifetime control. Browser-local appearance controls remain
  separate and are not repurposed as persistence owners.
- `DeviceMenus.ino` and `KeyboardNavigation.ino` own the current hard-coded `Session timeout: 15 min`
  item and immediate per-item `saveSettings` behavior. `src/ui.h/.cpp` owns the 240x135 Console screen;
  it currently renders token existence as browser presence. Serial `STATUS` has the same conflation.
- `handleFileDownload` is the only Web response owner that constructs raw HTTP headers and writes
  directly to `server.client()`. Every other mapped response uses WebServer header serialization.
  Therefore a refreshed session cookie for a successful file download must be emitted by that raw
  owner using the same cookie formatter; `server.sendHeader` alone cannot reach its response.
- `tests/host_tests.cpp`, `tests/web_console_ui_test.mjs`, `tools/hardware_web_e2e.mjs/.ps1` and the
  existing serial-held Web Console lifecycle are the proportional retained proof owners. They must be
  extended in place, not replaced by a new runner. The generated `src/web_console_asset.h` remains
  owned solely by `tools/embed_web_console.mjs`.

### Frozen minimal design and legal transitions

1. Add a typed `WebSessionLifetime` setting with exactly four legal enum values. Missing NVS state
   migrates to 15 minutes without a write. A present wrong NVS type or out-of-range value fails with an
   explicit settings-load error. `saveSettings` rejects invalid enum state, writes one bounded U8 key,
   verifies the stored type/value and only then permits the caller to adopt the candidate.
2. Keep the few portable lifetime, cookie-policy and wrap-safe expiry helpers in the existing
   `src/web_console.h/.cpp` owner, with the typed setting in `src/app_types.h`. Add no
   `web_session` files, registry abstraction, source-list plumbing or parallel runtime framework.
   Tokens, CSRF and aggregate presence stay in `web_console.cpp`.
3. Finite choices enforce server-side idle limits of 900, 3,600 and 28,800 seconds. Each successful
   authenticated non-presence request refreshes the server timestamp and its cookie with the matching
   `Max-Age`. One request-scoped refresh decision prevents duplicate cookie headers when storage guards
   and handlers both authenticate. WebServer-managed responses serialize that decision with
   `server.sendHeader`; the raw `handleFileDownload` success response writes the same formatted
   `Set-Cookie` line into its own raw header without queueing it through `server.sendHeader`, while
   that handler's WebServer-managed error responses use the normal serializer. Presence POST validates
   without touching the timestamp
   or emitting `Set-Cookie`. Until reboot emits a browser session cookie without `Max-Age` and never
   timer-expires. The server remains authoritative if a stale browser cookie survives an expiry or
   reboot. The Settings POST is the sole ordering exception to the ordinary guard: it
   authenticates/validates CSRF without a touch or cookie, then owns exactly one explicit old-or-new
   touch/cookie decision described next.
4. Web Settings first validates the current token and CSRF without changing activity, parses a candidate
   without modifying `consoleSettings`, and treats the submitted save as an authenticated activity. Any
   validation or `saveSettings` failure touches the current idle timestamp, emits exactly one cookie
   under the old runtime policy, returns the specific error, and retains that policy. Only after the NVS
   write and verification succeed does the handler adopt the candidate, touch the same timestamp once,
   emit exactly one cookie under the new policy and return success. This ordering cannot emit an old
   success cookie, duplicate old/new cookies, or adopt before durability. Device selection cycles
   15 min -> 1 h -> 8 h -> Until reboot -> 15 min through its existing menu item and adopts the
   candidate only after the existing settings save succeeds.
5. Register POST on the existing `/api/session` URI for one bounded heartbeat operation. It requires
   the matching current cookie and constant-time CSRF, requires an empty body, accepts no tab identity,
   validates without refreshing authentication, records `millis()` in one aggregate
   `lastHeartbeatAt` timestamp, sets one initialized flag and returns 204. Missing or invalid
   authentication/CSRF is an explicit failure with no state mutation. No heartbeat value is returned,
   logged, placed in a URL or persisted.
6. Each visible document sends the same non-overlapping heartbeat immediately, then eight seconds
   after each completed attempt. Hidden documents stop; `visibilitychange` back to visible sends one
   immediate attempt. There is no per-tab ID, registry, capacity error, leave protocol, request tab
   header or stored browser identity. P6-03 adds no `pagehide`/`sendBeacon` request because aggregate
   expiry is authoritative; any later optional hint still cannot clear aggregate presence. With tabs
   A and B, closing A has no
   adverse effect because visible B continues the aggregate heartbeat; after every visible tab stops,
   the aggregate expires from the last accepted timestamp.
7. Aggregate Connected is true only when initialized and the unsigned wrap-safe age is less than
   24 seconds. Known synchronous foreground owners that can block heartbeat processing show their
   existing operation state or a compact Busy state before blocking; during that interval the
   presence claim is unobservable, not Connected. At handler return, clear Busy and evaluate the
   original timestamp immediately, with no renewal, post-handler refresh, queued-signal assumption or
   grace pass. Only a subsequently accepted heartbeat restores Connected. The existing File Download
   URL, method, validation, synchronous streaming and transfer limits remain unchanged.
8. The Console loop, already the only single-threaded state owner, expires aggregate presence and
   finite authentication without waiting for another HTTP request whenever it is available to run.
   It rerenders only when aggregate authentication, presence or Busy presentation changes. Auth
   expiry, logout, token replacement, End Console, Python reboot handoff and teardown clear the
   aggregate initialized flag. Presence expiry never clears authentication. Device and public session
   state show Authentication and Browser presence separately; the screen uses `Browser connected`,
   `Waiting for browser` or Busy/operation state, and the Web shell exposes authenticated lifetime plus
   current presence without reviewer simulation controls.

### Failure, reboot and durable-state windows

- Before lifetime persistence, old valid NVS and current runtime policy remain. During the existing
  multi-field `saveSettings`, power loss or a storage failure can leave the old or new U8 value; no new
  transaction layer is introduced. A returned write/verify failure leaves the running policy old and
  reports the exact error. On reboot, load accepts only one exact enum and otherwise fails closed.
- After verified NVS success but before the Web response is observed, the choice and current runtime
  policy can already be new. Server expiry is authoritative; a lost cookie-refresh response may cause
  an earlier client-side login, never a session beyond the selected server limit. The next accepted
  ordinary request emits the current policy again.
- Token and presence mutations are RAM-only. A crash/reboot clears both before HTTP resumes; an old
  cookie therefore receives 401 and cannot recreate either state. A fresh password login creates the
  only new token/CSRF authority. Explicit logout clears aggregate presence globally by existing design;
  heartbeat expiry never logs out.
- A missed, rejected, hidden-tab or browser-killed heartbeat has no trusted side effect. The aggregate
  ages out at 24 seconds from its last accepted timestamp whenever the server loop is available.
  Network/server serialization can delay observation; while a synchronous foreground handler owns the
  server, Busy replaces any presence claim. Handler completion never advances the timestamp or adds
  grace, and no unprocessed heartbeat or beacon is assumed delivered.

### Adopted primary-source constraints

The exact local dependency is M5Stack board package 3.2.1 with embedded Arduino-ESP32/WebServer 3.2.0
(`de184bd0`) and ESP-IDF libraries `idf-release_v5.4-2f7dcd86-v1`. Its WebServer handles one client and
one current handler synchronously, closes each response connection, retains only explicitly collected
headers, supports method-specific handlers on one URI, parses POST arguments before URL arguments and
serializes application-owned `Set-Cookie` text. `millis()` is a boot-relative unsigned 32-bit
truncation, so elapsed subtraction is correct for 24 seconds through 8 hours across wrap; Until reboot
must be an explicit sentinel, not a large deadline. The shipped `handleFileDownload` bypasses
WebServer's response serializer by building and writing its raw response header directly, so its
authenticated success path must include the shared formatted cookie line at that exact owner.

The W3C Beacon processing model at `https://w3c.github.io/beacon/#sendbeacon-method` defines a POST with
credentials included, no response callback and no custom request-header facility; a true return only
means queued, not delivered. The WHATWG page-visibility model at
`https://html.spec.whatwg.org/multipage/interaction.html#dom-document-visibilitystate` exposes exact
visible/hidden state and fires `visibilitychange`; it also notes that hiding can throttle browser work.
The page lifecycle and Beacon sources therefore support only an optional best-effort hint that cannot
clear aggregate presence; expiry from the last accepted visible heartbeat is authoritative.

### Smallest frozen proof matrix

| Requirement or forbidden effect | Smallest retained proof |
| --- | --- |
| Four exact choices, strict decode, finite idle expiry, Until reboot and `millis()` wrap | Existing host suite executes the production helpers at just-before/at/after 15 min, 1 h and 8 h, Until reboot at arbitrary elapsed values, invalid enum input, and wrap. No duplicated oracle state machine or new source-list plumbing. |
| Aggregate presence ownership | Existing host suite proves uninitialized Waiting, heartbeat initialization/refresh, 23,999/24,000 ms boundary, wrap-safe expiry and authentication-clear reset using the production expiry helper. |
| Persistent setting plus Device/Web owners | Existing WebUI tests check the stable select/status IDs, four values, one Settings save producer, Device label/cycle/save source owner, syntax and generated-asset equality. One bounded direct observation is planned to start from an unauthenticated final-image request, round-trip all four values through the existing complete Settings payload, reject a malformed lifetime before other fields/save, explicitly log out an Until-reboot session, reject its stale cookie, and finish on one coherent 15-minute baseline. It reports only status/count/policy booleans and leaves API/Wi-Fi configuration unchanged. |
| Cookie versus heartbeat independence | The accepted auth-only interval proves finite 15-minute cookie policy and repeated heartbeat without idle refresh. The planned direct Settings observation covers finite Max-Age versus Until-reboot session-cookie policy, successful new-policy ordering, malformed-input old-policy preservation, explicit logout/stale-cookie rejection and final 15-minute baseline. The planned tiny File Download composition checks the raw success response carries the current policy without changing its URL, method or expected bytes. No proof prints or persists cookie/CSRF values. |
| Real multi-tab and last-heartbeat semantics | One actual two-tab browser observation starts A+B, closes A while visible B continues heartbeat and remains Connected, then stops the last visible heartbeat and observes Waiting by the 24-second boundary while the same cookie remains authenticated. No per-tab identity, leave or beacon-delivery claim is made. |
| Serialized foreground operation | The heavy greater-than-24-second transfer runtime is removed from the proof, not from product behavior. Independent complete writer inventory plus production helper tests prove that only init/reset and an accepted heartbeat change the aggregate timestamp/initialized state; Busy begin/end do not mutate or branch on its age, and Device/session JSON evaluate the same original timestamp after Busy clears. The planned replacement is one accepted heartbeat, a locally owned 26-second interval with no browser heartbeat producer, one successful ordinary tiny exact-owned nonempty File Download with expected bytes and raw current cookie policy, an immediate authenticated/Waiting GET, then one accepted heartbeat and Connected. Any begin/end timestamp renewal would make the GET Connected and fail. This replacement is planned and not PASS until observed; Busy during execution and deadline crossing inside a long handler remain source/composed evidence, not runtime claims. |
| Finite expiry and Until-reboot invalidation | One real 15-minute sliding-idle/heartbeat interval proves the runtime guard rejects heartbeat after the refreshed finite deadline while repeated heartbeat itself never refreshes authentication. The inspected Console-loop call owns autonomous expiry; a GET after a silent interval would itself invoke the same expiry guard and is therefore not claimed as prior loop-state observation or repeated as a second 15-minute test. Final-image startup rejects a protected request before login; the production helper proves Until reboot has no timer expiry; a real explicit logout through the shared clear owner makes the old in-memory cookie receive 401 before fresh login. Source review confirms token/CSRF are RAM-only and startup clears them before WebServer request handling. No standalone physical reboot carries a live test cookie. |
| Device state, resources and cleanup | Same-run serial `STATUS` distinguishes authentication from post-handler Connected/Waiting only; it cannot observe Busy while the synchronous handler owns the loop. Busy is covered by the inspected Device-render call path and post-return runtime state, without an in-handler serial claim. Direct Device observation checks the 240x135 screen when an existing capture path is available. Before/after flash, free heap, largest block, stack and latency preserve the 70 KiB floor. Finally establish one coherent 15-minute baseline, allow aggregate presence to expire, close only task-created browser tabs, remove the exact-owned tiny fixture/captures, retain Wi-Fi/API configuration, clear in-memory secret references without output, send one `EXIT`, and require exact `WEB_CONSOLE result=stopped`. Restoring unrelated disposable selection/settings is not required. |

### Frozen expected write set and review gate

After Architect's explicit P6-03 PRE-EDIT GO, the exact row write set is `ROADMAP.md`,
`src/app_types.h`, `src/storage.cpp`, `src/web_console.h/.cpp`,
`src/web_console_routes.h/.cpp`, `src/web_console_state.cpp`, `src/ui.h/.cpp`, `DeviceMenus.ino`,
`KeyboardNavigation.ino`, `assets/web_console.html`, generated `src/web_console_asset.h`,
`tests/host_tests.cpp`, `tests/web_console_ui_test.mjs`, `tools/hardware_web_e2e.mjs/.ps1`, and this
active trace. No `web_session` files, workflow source-list change, new runner, source snapshot,
response framework or broad recertification is planned. `tools/device_regression.ps1`,
`SerialDiagnostics.ino`, unrelated production, old tests/harnesses and P6-04+ behavior are outside the
planned write set and remain preserved.

No production edit is authorized by this freeze. P6-03 remains the sole `in_progress` row pending
Architect's explicit PRE-EDIT GO on the corrected short delta; no new reviewer loop is required.

The fresh independent reviewer returned `P6-03 PRE-EDIT REVIEW STOP` before any production edit. It
identified exactly two blockers: Settings authentication preceded persistence while WebServer only
appends response headers, so old/new cookie ownership was ambiguous; and unconditional completion
refresh could resurrect a closed tab while the headerless direct File Download path was not covered.
At 2026-09-10T22:58:21+03:00 the freeze above was corrected without changing its scope or write set:
Settings now has one explicit old-on-failure/new-after-durability ordering, and completion never renews
presence; the existing download becomes a body-owned same-route POST and serialized requests receive
only one opportunity to consume a genuinely queued signal. The proof matrix now includes rejected-save
cookie policy and greater-than-24-second stay-open versus close/kill observations. No production, test,
harness, Device, build or external state changed. The same reviewer performed its one blocker recheck.

That recheck returned a second `P6-03 PRE-EDIT REVIEW STOP` at
2026-09-10T23:01:41+03:00. It accepted the corrected Settings cookie ordering and retained only the
long-download case: a browser download manager may keep the authenticated transfer socket alive after
the last visible tab closes, while the current one-client synchronous WebServer cannot accept either
that tab's queued heartbeat or leave hint until the stream ends. During that interval an open visible
tab and a closed tab with a retained browser-managed transfer have identical device-observable state.

The current frozen active-transfer exception therefore does not satisfy the literal
`ROADMAP.md:651-652` clock for that combined case and is not approved for production. Meeting both
observations would require at least one materially different owner: a concurrent/background transfer,
a second server/transport, a browser file-streaming API unavailable on the current local-HTTP origin,
or aborting/limiting the already shipped large-file download. The first two conflict with the locked
P6 non-goals, the third is not a supported portable interface, and the fourth would remove or narrow
completed behavior. No further reviewer loop is started. P6-03 remains `in_progress`, production stays
frozen, and the exact conflict plus smallest preservation-first option is routed to Architect for an
authoritative scope/ownership decision before this package can receive PRE-EDIT GO.

Architect resolved ownership at 2026-09-10T23:14:10+03:00 after personally checking
`handleFileDownload`, the Console loop, pinned WebServer semantics and the frozen package. The
preservation-first decision keeps the existing synchronous transfer, rejects asynchronous download,
a second server, background ownership and transfer restriction, and records a cost/UX-based scope
reduction rather than runtime evidence: while the synchronous WebServer can process requests, presence
expires from the last visible-tab heartbeat within 30 seconds; while a foreground handler blocks that
processing, presence is Busy/unobservable, and handler return evaluates the original timestamp without
renewal or grace.

The corrected pre-edit delta above replaces the proposed per-tab registry with one aggregate
initialized flag and last-heartbeat timestamp, removes IDs/leave/capacity/header/download-conversion/
grace machinery and new source files, retains the accepted Settings old-policy-on-failure and
new-policy-after-verified-save ordering, and maps cookie output to both WebServer-managed responses and
the actual raw File Download header owner through one formatter. Proof is reduced to the resulting
existing-owner behavior: exact lifetime persistence/cookie ordering, real two-tab heartbeat expiry and
authentication independence, one unchanged long operation showing Busy then original-timestamp
evaluation without resurrection, planned expiry/reboot evidence, resources and exact-owned cleanup.
`ROADMAP.md`, the locked product contract, matrix, design, proof and write set now carry that decision.
No production, test, harness, build or Device state changed. P6-03 remains the sole `in_progress` row
pending Architect's immediate personal PRE-EDIT verdict; no new reviewer loop is started.

Architect personally reviewed the corrected canonical contract, current source-owner inventory,
raw File Download cookie boundary, reduced proof matrix, sole `in_progress` row and exact write set,
and returned explicit `P6-03 PRE-EDIT GO` at 2026-09-10T23:29:36+03:00. This authorizes only the
frozen P6-03 implementation and proportional verification. It does not authorize completion,
staging, commit or publication before the separate closure gate.

P6-03 entered a confirmed external platform-blocker interval at
2026-09-10T23:45:04.817+03:00. The platform rejected the coherent authentication implementation
because changing session expiry, cookie refresh, CSRF handling, browser presence and cleanup requires
more specific trusted-user authorization than the publication permission currently available to the
phase task. Architect confirmed that its pre-edit GO cannot bypass that refusal and paused the active
work clock.

The preserved partial implementation changes exactly eight production files:
`src/app_types.h`, `src/web_console.h`, `src/storage.cpp`,
`src/web_console_state.cpp`, `src/ui.h`, `src/ui.cpp`, `DeviceMenus.ino` and
`KeyboardNavigation.ino`. They add the four-value typed lifetime contract and pure timer helpers,
strict existing-owner NVS persistence, public Settings state, the Device lifetime selection and
separate Device presentation types. The rejected runtime authentication/heartbeat/route patch was not
applied; tests and harnesses are unchanged. This incomplete state is not a build, verification or
acceptance candidate. No rollback, further patch, build, upload, test or Device action is permitted
until the external authorization condition changes.

The external platform-blocker interval ended at 2026-09-11T00:01:35.041+03:00 after Architect
relayed the user's new exact informed authorization, given after the platform refusal: the user
explicitly permits P6-03 authentication lifetime choices of 15 minutes, 1 hour, 8 hours and Until
reboot, together with the required cookie and CSRF-processing changes without disabling protection,
and acknowledges that longer choices preserve authorized access for longer. The interval from
2026-09-10T23:45:04.817+03:00 through 2026-09-11T00:01:35.041+03:00 remains recorded as 16 minutes
30.224 seconds of paused external-blocker time; active elapsed work resumes without being reset.
The existing corrected `P6-03 PRE-EDIT GO` is again operative, while closure, staging, commit and
publication remain separately gated.

At 2026-09-11T00:04:59.709+03:00 the platform rejected the first coherent runtime edit after the
relayed authorization. Its exact ownership finding was that the authorization exists only in
untrusted cross-task tool output rather than a trusted user message in this phase task; it therefore
still refuses the combined session-expiry, cookie-refresh, CSRF, route, presence and cleanup change.
No part of that runtime patch was applied, and the eight-file partial production set remains exactly
as recorded above. The active clock ran for 3 minutes 24.668 seconds after the relayed unblock, then
paused again at this renewed external blocker. This task will not split, retry through another
executor or otherwise bypass the refusal.

The renewed external platform-blocker interval ended at
2026-09-11T00:20:38.416+03:00 when the user supplied the required authorization directly in this
phase task: P6-03 may implement the 15-minute, 1-hour, 8-hour and Until-reboot authentication
lifetimes and the necessary cookie and CSRF-processing changes without disabling CSRF protection;
the user explicitly acknowledges that longer choices preserve authorized access for longer. The
interval from 2026-09-11T00:04:59.709+03:00 through 2026-09-11T00:20:38.416+03:00 remains recorded
as 15 minutes 38.707 seconds of paused external-blocker time. The active clock resumes without being
reset under the existing corrected `P6-03 PRE-EDIT GO`; the previously attempted coherent runtime
patch remains unapplied, and closure, staging, commit and publication remain separately gated.

At 2026-09-11T00:24:57.846+03:00 the user directly granted standing authorization for all already
approved Phase 6 work and its publications and instructed the agents not to request further
conversational permission. This decision covers normal in-scope implementation, canonical edits,
proportional verification, build/upload/COM8/local Web work, exact-owned cleanup and publication;
it does not expand Phase 6, waive its review and closure gates, authorize Phase 7, expose or alter
secrets/Wi-Fi credentials, or permit the prohibited readiness-recovery chain. The first coherent
P6-03 runtime server edit was then accepted across the existing Web Console and route owners; it
retains CSRF protection and is implementation progress only, not verification or closure evidence.

At 2026-09-11T01:02:52.9599225+03:00 Architect reduced only the dedicated physical
stale-cookie reboot experiment before any such run. The product contract remains unchanged:
Until-reboot sessions have no timer expiry, token and CSRF authority remain RAM-only, and startup
clears both before the sole WebServer request loop begins. The retained proportional proof combines
final-image unauthenticated rejection before login, the production no-timer helper/cookie behavior,
real old-cookie rejection after explicit logout through the same clear owner, fresh login, and
personal source review of startup ordering and absence of token persistence. No live token is claimed
to have crossed a standalone physical reboot. This avoids a one-off reset/process rendezvous that
would expand the existing harness and duplicate unchanged boot machinery; it does not weaken the
Until-reboot behavior or authorize any readiness-recovery action.

At 2026-09-11T01:08:46.9671702+03:00 the fresh independent code review returned STOP on three
active-row implementation gaps and one already-classified proof impossibility. The exact correction
delta is frozen before edits: balance Busy only around the identified size-dependent file-range save,
Project/Chat duplication and chat/bundle export/import owners; retain authenticated multipart Busy
through all parser callbacks and clear it at the existing single-client request boundary immediately
after `server.handleClient()`; and expose the same authentication/presence state through one
renderer in a duplicate-ID-free responsive shell surface. Pinned `Parsing.cpp` confirms
`UPLOAD_FILE_END` ends one part rather than the whole form, so it is not the cleanup owner. Serial
`STATUS` remains a post-handler authentication/Connected/Waiting observation and makes no in-handler
Busy claim. The same reviewer will perform its single blocker recheck after cheap checks; no build,
upload or Device proof begins before that recheck. No backend transfer behavior, P6-05 styling,
transport, reset mode, per-upload registry or recovery path is added.

The same reviewer performed its single blocker recheck and accepted the synchronous-owner Busy
wrappers, multipart Busy lifetime, request-boundary clear and narrowed serial proof. Its sole
remaining finding was that a successful heartbeat updated only the desktop presence node. The
correction at 2026-09-11T01:37:10.2196403+03:00 introduced one shared browser-presence renderer used
by both initial session rendering and heartbeat success, updated the responsive post-204 assertion,
and regenerated the embedded asset (`source=144787`, `gzip=36040`). Observed cheap evidence is
`WEB_CONSOLE_UI_TEST result=pass`, Node syntax pass, PowerShell parser pass, the direct Node HTTP-204
boundary assertion pass, current CI-equivalent `host_tests: PASS`, and `git diff --check` pass apart
from line-ending warnings.

Architect then held build/upload/Device execution on four harness/proof findings, without reopening
production: buffered responses now use a null body for HTTP 204 and tag only fetch/body-read failures
as transport loss; a nonce-bound multipart rejection supplies the same invalid traversal name in
both query and upload filename and requires the workspace files revision to remain unchanged; a
tagged transport loss exits distinctly so Node performs no further HTTP cleanup and PowerShell sends
no further Device command or fixture cleanup on that terminated path; and the indistinguishable
second 15-minute GET-based “autonomous” observation was removed in favor of the inspected loop owner
plus the one real finite sliding-idle/heartbeat expiry interval described in the matrix. On a
completed-response assertion failure with transport still healthy, Settings restoration remains
enabled and the existing exact large-fixture cleanup now requires a second idempotent absence result
before removing its ledger. Retained evidence now derives `restored_settings_observed` from the
post-restoration Settings response. No production behavior, reset/recovery path, second request
framework, fixture ledger or P2 Device verification was added. Hardware execution remains held until
Architect reviews this exact bounded correction delta.

Architect returned compile-only GO and retained the upload/Device hold for two final harness seams
plus the pre-login observation owner. At 2026-09-11T01:45:35.8282850+03:00 the one pinned final-source
compile passed with 3,630,830 flash bytes and 65,908 global bytes, leaving 261,772 bytes for local
variables. Parsed `build/p3-phase/build.options.json` is 1,736 bytes with SHA-256
`20ba11ee73700a2d4a591c7c8da0516c89e807bf0e66d8257ed88e8cc834c998`; it contains the exact required
FQBN once and two references to the same unique resolved M5Stack ESP32 3.2.1 directory, with no other
core. No upload or Device request was performed.

The bounded harness correction now keeps the streamed response in the existing request owner and,
on any status/cookie/Content-Length assertion before body completion, cancels that response body in
`finally` before any healthy-path HTTP restoration can begin; a cancellation/body-read failure remains
tagged as transport loss. PowerShell now classifies Node exit 20 immediately after process completion,
before any fallible capture read or log write, so its finalizer cannot send `EXIT` or another Device
command on that terminated path. The P6-only credential owner sends one unauthenticated GET to the
protected session endpoint and requires 401 with no cookie before the first password login; the output
retains only the safe `protected_request_before_login=pass` observation. Node syntax, PowerShell parse
and `git diff --check` pass after this change. Upload and Device execution remain held pending
Architect's immediate review of only these final seams.

Architect returned `P6-03 EXECUTION GO` for one normal upload and one focused selector. The exact
compiled image uploaded once through COM8 with every written flash segment hash verified; no NVS or
microSD erase was requested. The focused path then observed its sole initial `PONG`, exact 320 MiB
fixture setup pass (`free_heap` 121,920 -> 121,996, `largest_heap` 60,404 -> 60,404 and minimum heap
110,348 -> 110,348), and `WEB_CONSOLE result=ready`. Its first HTTP operation, the unauthenticated
GET `/api/session` before login, failed at transport before any HTTP response with the safe marker
`P6_SESSION_TRANSPORT_FAILURE HTTP GET /api/session transport failed: fetch failed`.

At 2026-09-11T01:55:03.1256001+03:00 that Device/Web path terminated and failed. Node exited with the
dedicated transport code; PowerShell sent no `EXIT`, readiness probe, reset, HTTP request, upload or
Device cleanup after the failure, closed only local serial resources, and reported the exact fixture
cleanup unresolved. The owned 320 MiB fixture and its local ownership ledger remain intentionally
retained. No acceptance claim is made from this run, the path will not be reused, and production plus
its oracle are frozen pending Architect ownership classification. Only local capture/log contents
were read afterward.

At 2026-09-11T02:03:41.2176459+03:00 an earlier interpretation of the user's observation was
corrected: the current failed run did not visibly prove the IP/password screen; the only retained
current-run observations are the serial `WEB_CONSOLE result=ready` marker, which source emits before
`renderConsoleScreen()`, and the user's report of a dark screen with no visible response to keys.
The user then independently restarted the device after that proof path had already been abandoned
and reported that its appearance was normal again. This is external restoration only, not measured
readiness, failure ownership, reboot evidence or P6-03 acceptance. It does not resolve or authorize
declaration of cleanup for the retained 320 MiB fixture/ledger, and the original Device/Web path
remains frozen without a repeat of the unchanged composite scenario.

Architect's bounded read-only ownership review at 2026-09-11T02:07:30.5913201+03:00 separated the
dark-display observation from the HTTP failure. A reachable pre-existing path lets the ordinary
screen-sleep owner set brightness to zero, continue accepting serial commands while sleeping, and
enter Web Console without restoring brightness or clearing the sleeping state; the Web Console
Enter-key path redraws but does not restore brightness. This boundary is unchanged from the
published baseline and belongs to the pending P6-06 Device UI row. It makes the observed ordering
plausible but does not prove the failed run's actual sleep setting, render completion or root cause,
so no P6-03 production change follows from it.

The independent `/api/session` source review found no deterministic transport failure in the P6-03
authorization handler. The GET route, empty-session 401 branch and shared exact-length JSON sender
are unchanged from the published baseline; pinned WebServer 3.2.1 matches the new POST route by exact
method, and a server-side JSON write failure would have emitted `WEB_TRANSPORT result=failed`, which
is absent from the retained capture. The observed safe `fetch failed` marker occurred before the
45-second request limit, but the wrapper did not retain Node's nested transport cause. Because serial
ready precedes both the initial render and the first `server.handleClient()`, handler entry is not
proven. HTTP-failure ownership therefore remains unresolved between host/network/runtime reachability
and a pre-handler lifecycle boundary, with current evidence disfavoring the P6-03 auth logic. No
same-hypothesis Device or composite-test retry is authorized; the next proof must be materially
smaller, avoid another 320 MiB setup, and require no physical recovery dependency.

Architect returned bounded local-correction `GO` for the exact retained-fixture adoption block in
`tools/hardware_web_e2e.ps1`, reviewed at file SHA-256
`0EEC891DA65D0F669D2B2DC32BFB3DFA7A81CFA6DD58AA5328884894E041513B`. The `p6-session` branch now
requires the existing strictly validated, setup-complete and still-unverified ledger, adopts its
nonce and existing cleanup responsibility, and performs no pre-run cleanup, ledger deletion, nonce
generation, fixture setup or fallback. The ordinary `large-stream` branch and the existing normal,
idempotent and failure-finalizer cleanup owners remain unchanged. PowerShell parsing and diff checks
passed. Setting the existing `largeStreamSetupAttempted` state here denotes adoption of cleanup
responsibility only and is not a new setup observation. This resolves only the local runner-reuse
mismatch; HTTP ownership/readiness, Device acceptance and exact fixture cleanup remain unverified.

Architect then authorized one materially corrected post-restoration lifecycle using the reviewed
runner and already flashed image, with no build, upload, reset, preliminary probe or new fixture
setup. The run began at `2026-09-11T06:58:32.9174742Z`, observed its sole `PONG` and Web Console
startup through `WEB_CONSOLE result=ready`, and performed no `P2LARGESETUP`. At
`2026-09-11T07:30:44.0623074Z`, 1,931.145 seconds after start, it terminated on the safe marker
`P6_SESSION_TRANSPORT_FAILURE HTTP POST /login transport failed: fetch failed` with no JSON stdout.

The retained capture cannot identify that late POST as either the intended final fresh login after
the finite-expiry check or the failure-path restoration login after an earlier late assertion. The
existing cleanup catch prioritizes and rethrows a transport error over the original test error, and
the safe transport logger omits the nested socket cause/code. Consequently this run makes no full
PASS claim and no claim that a particular authentication assertion failed or passed. Its finalizer
sent no `EXIT`, cleanup, readiness probe or other Device command after the transport failure. The
exact-owned large-stream ledger remains present at 347 bytes with cleanup unresolved; real two-tab
browser evidence was not run. This second failed path is frozen, and P6-03 runtime acceptance remains
incomplete pending ownership classification from genuinely new evidence.

At 2026-09-11T10:50:24.5518808+03:00 the bounded local diagnostic-owner correction in
`tools/hardware_web_e2e.mjs` retained the existing no-restoration-after-primary-transport guard
unchanged. Transport classification now retains only a fixed allowlisted machine code or name from
the direct error and at most one nested cause, otherwise `UNCLASSIFIED`; reports a fixed `primary` or
`restoration` stage; and, for a restoration transport failure, reports at most two validated canonical
`tools/hardware_web_e2e.mjs:line:column` locations from the original primary error, otherwise
`primary=unclassified`. The P6-only terminal marker emits only the typed failure, stage, machine value
and safe owned-source locations; no raw error message, cause or stack is attached or printed, and exit
20 plus the PowerShell fail-closed owner remain unchanged. Node syntax and `git diff --check` passed
apart from the existing line-ending warning. No Device, HTTP, browser, build, upload, reset, fixture,
credential or Wi-Fi action occurred. This is diagnostic evidence only; it neither classifies either
frozen run nor completes P6-03.

At 2026-09-11T11:04:10.0168323+03:00 Architect assigned the already-recorded complete-Python-source
navigation gap without expanding Phase 6: P6-05 owns Web Pending to full source and return to the same
Pending identity, P6-06 owns the corresponding Device navigation and return to the originating Chat,
and P6-07 owns cross-surface integration proof. These rows reuse the P5 execution, approval, identity,
security and endpoint owners unchanged; an authoritative P5-boundary defect must be reported to that
owner rather than repaired silently. This is an ownership clarification, not pre-edit authority for
P6-05 or P6-06.

The same read-only baseline clarification confirms that the editable asset is
`firmware/CardputerAssistant/assets/web_console.html`, generated only through
`tools/embed_web_console.mjs` into `firmware/CardputerAssistant/src/web_console_asset.h`. Contrary to
the older historical absence statements above, published `HEAD` already dynamically creates
`loadMoreProjects`, `loadMoreFiles`, `toggleProjectLink` and `projectLinkState` and binds their existing
handlers. P6-05 therefore owns their accepted presentation, stable reachability and truthful
loading/error/EOF states, not duplicate handlers or routes. No production, test, browser, HTTP,
Device, build, upload or reset action occurred. P6-03 remains the sole `in_progress` row and every
later row remains `pending`.

At 2026-09-11T09:37:03.902Z Architect accepted one bounded auth-only observation from the
pre-reviewed disposable sources with SHA-256
`E47BF73E94000C05447DC523DBBDEFAA2BCE17CFCD0065188D982103DDA15A79` for the Node observer and
`C6D49B62CC993C67F126E52FDBA930983CA2F070C100F45B55A1F39564CF6E7D` for its serial holder. The sole
run observed `PONG` at 371 ms, Web Console ready at 1,024 ms, manual login HTTP 303, and exactly one
baseline `GET /api/session` spanning observer 61-105 ms with HTTP 200, authenticated state, a CSRF
token, lifetime `15m`, cookie Max-Age 900 and the same session cookie. Empty heartbeat POSTs using
that explicit old cookie returned HTTP 204 without a replacement cookie through sequence 112 at
896,068/896,025 ms from the baseline request-start/body-completion bounds. Sequence 113 returned
HTTP 401 at 904,062/904,019 ms, followed by exactly one manual login HTTP 303 with a different cookie
at 904,157 ms and no subsequent session GET. The Console then emitted exact stopped at 905,295 ms;
the holder reported final pass and exit 0 at 905,300 ms.

This observation did not run a browser, Settings mutation, build, upload, reset, file operation,
large-stream setup or any other HTTP action. API credentials and Wi-Fi were not modified. The
existing 320 MiB fixture and ownership ledger remain untouched with cleanup unresolved, and real
multi-tab browser presence remains unverified. This evidence is not P6-03 closure, staging or commit
approval.

The subsequent single Architect-approved real-browser observation used the frozen disposable
sources with SHA-256 `61A0CAAEC6691A01E071D472AD12E260BD10FBA7391F84A2684CCA4CA69E437B`
and `982C48E529C89ACF04CB98921A02531E75CD7B534C7D0AE9726144C89A27634C`. It observed only `PONG`
at 373 ms, Web Console ready at 987 ms, Chrome launch at observer 223 ms and the shared-context
manual login HTTP 303 at observer 328 ms. It then emitted no page-A heartbeat or later safe marker
and remained running beyond its reviewed 120-second constant. The exact local process was
terminated without `EXIT`, retry, probe, reset, upload, recovery, Device cleanup or another HTTP
request. A read-only local process inventory afterward found zero exact observer Node/PowerShell
processes and zero Playwright headless Chrome processes.

The 120-second constant was not a watchdog around every awaited operation. This confirmed harness
defect explains the failure to terminate and report, but does not identify or explain the original
stall and does not assign it to production, hardware, Chrome or Device transport. No normal Console
stop, page heartbeat, multi-tab behavior, Waiting transition or P6-03 acceptance is claimed. The
observer sources remain only for bounded read-only classification; Device normal stop and the
existing 320 MiB fixture cleanup both remain unresolved.

Architect then approved one cleanup-only teardown of the exact unmatched Console session. Passive
buffer inspection found no classified readiness-loss marker; one and only one serial `EXIT` was
sent, exact `WEB_CONSOLE result=stopped` arrived, and local close/dispose completed in 356 ms. No
`PING`, `STATUS`, `CONSOLE`, HTTP, retry, reset, build, upload, recovery or fixture action occurred.
The user subsequently reported that the display had revived. No user reboot was reported after this
cleanup, and the observation does not prove key response, full Device health, browser behavior,
P6-03 acceptance or the cause of the original stall. It supplements service-teardown evidence only;
the failed browser proof remains failed and the existing 320 MiB fixture/ledger remains unresolved.

At the 2026-09-11T13:55:18.3803536+03:00 checkpoint, a bounded host-only capability preflight
established stepwise control without touching the Device or network: one interactive PowerShell
session returned its fixed marker, and one Node 22/Playwright 1.62.1 session launched the installed
Chrome channel, created one fresh context and two separate `about:blank` pages through separate
submitted commands, and observed both documents as `visibilityState=visible` and `hidden=false`.
Exact Node/browser ownership was retained before Device work; no recreation loop occurred.

Architect then approved one direct two-tab observation in those existing sessions. One `PING`
returned in 14 ms and Web Console became ready in 606 ms. A single ignored-credential login returned
HTTP 303 and cleared the local secret references. Page A then observed root HTTP 200, its own real
`POST /api/session` HTTP 204, a visible document, and the stable authentication/presence nodes as
Active/Connected in 376 ms; page B observed the same required results in 236 ms. With B's real
response waiter armed before A closed, B returned a post-close heartbeat HTTP 204 after 3,222 ms,
remained Connected, and closed normally in the same submitted command. No response-body completion
oracle, request interception or synthetic visibility was used.

The first attempt to sample Waiting did not send its planned GET: the controller submitted that
guarded command 62,765 ms after the retained B-response timestamp instead of at 26 seconds, so it
returned an explicit local scheduling failure before any request. Architect accepted the preceding
A/B observations and assigned this failure to controller scheduling across model/tool turns, not to
production or Device/HTTP transport; the two-tab stage remains preserved and was not replayed.

Architect authorized one materially smaller correction for only the missing last-visible-tab
observation. One exact-owned page C was created in the existing context. A single submitted Node
command then observed root HTTP 200, C's real heartbeat HTTP 204, a visible document and stable
Active/Connected nodes, closed C 23 ms after that response, owned the complete wait locally, and
started exactly one shared-context `GET /api/session` 26,007 ms after the response. The GET completed
at 26,030 ms with HTTP 200, `authenticated=true` and `browser_presence=waiting`; the full causal block
took 26,287 ms. Browser close returned disconnected within its 20-second controller bound, Node
exited zero, one and only one serial `EXIT` produced exact Web Console stopped in 43 ms, serial
close/dispose passed and PowerShell exited zero. No exact-owned page, browser, serial or interactive
session remains.

Architect accepted this combined A/B plus corrected-C evidence without changing the original
62,765-ms sample into a pass. It closes only the real aggregate multi-tab/last-heartbeat observation:
one closing tab did not hide the remaining live tab, and after the last visible heartbeat the same
authenticated context reported Waiting inside 30 seconds. P6-03 remains `in_progress`. This proof did
not change Settings, exercise the 1-hour, 8-hour or Until-reboot policies, run the foreground
Busy/unobservable boundary, prove final-image pre-login or explicit-logout stale-token behavior, or
touch the retained 320 MiB fixture and 347-byte ownership ledger. Row closure, staging, commit and
publication remain withheld.

At 2026-09-11T11:18:39.252Z the next P6-03 direct Settings/cookie/file observation was frozen as
planned and not PASS. It reuses the existing session, Settings, raw-download and P2-29 binary-fixture
owners; the expected write set is limited to the existing `tools/hardware_web_e2e.mjs`,
`tools/hardware_web_e2e.ps1` and this trace. No production file, new harness file, new fixture
contract, browser, Device, network, build, upload or reset is authorized by this freeze.

One normal Console lifecycle first issues one unauthenticated protected-session GET before login and
requires HTTP 401 with no cookie. After one login, the existing complete Settings form preserves all
current non-lifetime values, sends all five write-only secret inputs empty, sends all three clear
flags false and changes only `web_session_lifetime`. It round-trips `15m`, `1h`, `8h` and
`until_reboot`, requiring one unchanged-token cookie with Max-Age 900, 3600, 28800 or absent
respectively. From Until reboot, one direct malformed-lifetime POST must return 400 with the old
no-Max-Age policy and leave lifetime, revision and every other setting unchanged. Explicit logout
must emit one deletion cookie and the saved old cookie must then receive 401 without replacement.
One fresh login and one final `15m` save must leave Settings and Session at 15 minutes, active
authentication, Waiting presence and an exact successful Settings-revision delta of five, with
Wi-Fi identity and API/credential configuration unchanged. No secret, cookie, CSRF, SSID, endpoint
or credential-source value may be retained.

The same lifecycle then collision-checks and durably owns the existing P2-29 fixture
`p2_29_<nonce>.bin`: exactly eight bytes with SHA-256
`e57eec3c40ea8c6ce033eeb848f00dd2e8d86eeebe90777d9267620a96b574ae`. After upload, one accepted
heartbeat must return 204 with no cookie or body. A single locally owned 26,000-ms interval sends no
HTTP and has no browser heartbeat producer. One ordinary bounded raw download must return the exact
eight bytes, Content-Length 8 and one unchanged-token 15-minute cookie; an immediate Session GET
must remain authenticated and report Waiting. One further accepted heartbeat followed by Session
GET must report Connected. This composition makes no runtime Busy or in-handler deadline-crossing
claim; those remain source/helper evidence.

Successful cleanup removes only the ledger-owned tiny fixture, verifies zero remaining matches and
an idempotent complete result, then removes its validated ledger. The retained resource oracle is
free heap at least 70 KiB, largest block at least 28 KiB, positive stack margin and no more than
4,096-byte steady free/largest loss. Local authentication references are cleared, exactly one
`EXIT` is sent and exact `WEB_CONSOLE result=stopped` is required. A completed-response assertion
failure may use only the same exact cleanup and final 15-minute baseline while transport is healthy.
Any fetch, timeout or body-read failure is a typed transport termination: no later HTTP, serial
command, restoration or Device cleanup is allowed, and its exact ledger is retained for the existing
recovery owner. The unrelated retained 320 MiB fixture and 347-byte ledger remain separate,
unresolved and untouched.

At 2026-09-11T11:45:50.788Z Architect returned execution `STOP` and bounded harness-correction `GO`
for the frozen direct observation. The exact blockers were a P6 tiny download that could inherit the
45-minute large-stream timeout, and both `cleanupBinaryTextOwnership` catch boundaries converting
HTTP transport loss into an aggregate ordinary error. Architect additionally required an explicit
stable Settings snapshot containing returned configuration, provider identities and key-configured
booleans while excluding revision, selected lifetime and runtime/status fields. The current visible
screen appearance is user-reported only; it is not readiness or acceptance evidence and was not
probed.

The permitted in-place correction now keeps the original large-stream helper and suite unchanged,
routes only P6-03 through the existing P2-29 nonce/ledger owners, and gives its exact eight-byte raw
download the existing 45-second `maximumRequestMs` boundary whose `fetchWithin` owner reads the
complete response body before clearing the deadline. Both binary-ownership cleanup catches
immediately rethrow typed transport loss and aggregate only completed-response/assertion failures.
The direct Settings proof compares the explicit stable snapshot after every accepted save, after
the malformed rejection, after fresh login and after the final 15-minute save; four policy saves
plus final restoration are the only five accepted revision increments. PowerShell no longer adopts,
passes, verifies or cleans large-stream state for `p6-session`; it validates only the safe compact
evidence and the exact completed P2-29 ledger before removing that ledger. Node syntax, PowerShell
parse and `git diff --check` pass apart from existing line-ending warnings. No Device, HTTP,
browser, COM8, build, upload, reset, fixture or credential action occurred. Execution remains held
for Architect's focused review of the actual diff; the retained 320 MiB fixture and 347-byte ledger
remain untouched.

At 2026-09-11T11:54:09.400Z the sole Architect-approved compact `p6-session` Device/Web run
completed with process exit 0 on the reviewed source hashes. The normal lifecycle used one initial
PING, reached `WEB_CONSOLE result=ready`, performed no browser/build/upload/reset/recovery action,
then emitted exact `WEB_CONSOLE result=stopped`. The pre-login protected Session request returned
401 with no cookie. Settings round-tripped `15m`, `1h`, `8h` and `until_reboot`; their
accepted saves took 102, 101, 102 and 103 ms and both each save and following Settings GET returned
one unchanged-token `HttpOnly; SameSite=Strict; Path=/` cookie with Max-Age 900, 3600, 28,800 or
absent respectively.

The direct malformed lifetime returned 400, preserved the Until-reboot cookie policy and left the
Settings revision unchanged. The explicit logout returned one empty Max-Age 0 cookie; the saved old
cookie then received 401 without replacement. Fresh login and the sole final save established a
coherent 15-minute Settings/Session baseline. The accepted Settings revision delta was exactly five.
The explicit stable snapshot remained equal across all observations: Wi-Fi identity, API and
provider/preset identities and authority revisions, key-configured booleans and all other returned
configuration were unchanged; five write-only fields were empty, three clear flags were false and
no raw secret field appeared.

The exact P2-29 nonce had zero reserved-name collisions. Its durable ledger preceded upload of the
eight-byte fixture with SHA-256
`e57eec3c40ea8c6ce033eeb848f00dd2e8d86eeebe90777d9267620a96b574ae`. The first heartbeat
returned 204 with no cookie or body in 97 ms. After one locally owned 26,010-ms interval with no
HTTP or browser heartbeat, the ordinary raw download completed in 90 ms with HTTP 200, exact raw
headers, Content-Length 8, byte-for-byte content and one unchanged-token Max-Age 900 cookie.
Immediate Session state remained authenticated and reported Waiting. A second 204 heartbeat in
82 ms followed by Session GET reported authenticated Connected.

Resources measured free heap 94,264 -> 93,124 bytes (1,140-byte loss), largest block
31,732 -> 31,732 bytes (zero loss), and positive stack margin 5,704 -> 5,080 bytes. Two-pass
fixture cleanup reported zero remaining matches, `cleanup_complete=true` and idempotent success;
the exact P2-29 ledger and its temporary file are absent. The two exact-owned Node stdout/stderr
captures were removed and absence verified. The retained 3,399-byte run log has SHA-256
`56AE32CF3DC56B1C53AF56F9BB01A53C9667856780D930D2DD3A336B23779277`. The unrelated retained
large-stream ledger remains present at 347 bytes with current SHA-256
`AE6D5AF5283804EC08864182BF68E6E90453B43C5578AA8767FA7E02CD399550`; the reviewed harness has
no P6 path that reads or mutates it. P6-03 remains `in_progress`, production is frozen and row
closure, staging, commit and publication remain withheld for mandatory Architect closure review.

Architect's closure review accepted the compact P6-03 functional observations but returned two
independent STOPs: the retained exact-owned 320 MiB cleanup debt and uncalled P6-specific
heavy-stream proof debris. It first authorized one cleanup-only serial lifecycle with no PING,
STATUS, HTTP/Web Console, fixture creation, build, upload, reset or recovery. The preflight required
the unchanged nonce `1789080570927`, exact 347-byte ledger SHA-256
`AE6D5AF5283804EC08864182BF68E6E90453B43C5578AA8767FA7E02CD399550` and zero sidecars.

That first lifecycle began at `2026-09-11T12:22:58.3019649Z`, completed a passive drain without a
classified readiness-loss marker and issued exactly one `P2LARGECLEAN` write and flush for the owned
nonce. Before reading its response, the one-off PowerShell runner rejected the valid empty serial
tail because its mandatory `InitialTail` string parameter lacked empty-string permission. No cleanup
response was observed and no second command was sent. The runner entered its close/dispose finalizer,
deleted no ownership artifact and retained the unchanged ledger with zero sidecars. The sanitized
292-byte failure log has SHA-256
`C1151C8834B801E416F8A74FCDCA0BC7257ED6D14931FFE202BAA6E884A2A022`. Architect classified this as
a local one-off runner defect rather than Device readiness or transport loss and authorized one
corrected cleanup-only observation of the unknown post-command state.

The corrected observation began at `2026-09-11T12:28:15.5115227Z` after the same ledger/hash/nonce
preflight. Its fixed 1.5-second passive drain observed zero `P2LARGECLEAN` responses and no readiness-
loss marker. It therefore sent one exact same-nonce observation command and received no cleanup
response of any kind within the single fixed 120-second deadline. No wrong nonce, malformed/failing
response, read/write exception or classified readiness-loss marker was observed. The fail-closed path
closed/disposed serial, did not send the final idempotency command and deleted nothing. The ledger is
still byte-for-byte unchanged with zero sidecars. The sanitized 311-byte timeout log has SHA-256
`09454355F2DADB135DA364C3E795A881A38227F280466949E74FCE655FA32304`. Exact Device deletion,
absence and idempotence therefore remain unproven. Architect froze this transport path: no further
COM8, HTTP/Device probe, reset, retry or recovery is allowed, and both logs plus the ownership ledger
remain retained for read-only review. This is a cleanup blocker, not a P6-03 production failure.

The independent dead-code STOP was corrected without touching production or any called test. The
deletion-only change removed the four unreferenced constants `p6SessionHeartbeatIntervalMs`,
`p6SessionPresenceTimeoutMs`, `p6SessionExpiryMarginMs` and `p6SessionRefreshDelayMs`, plus the
uncalled helpers `expectP6SessionFailure`, `maintainP6SessionHeartbeatsThrough`,
`p6SessionChatSnapshot`, `streamP6SessionFixture` and `p6SessionFilesRevision`; no replacement was
added. Exact reference search now finds zero occurrences of all nine names. The shared called
large-stream owner remains intact: `maximumLargeStreamMs` still bounds
`streamWorkspaceFileSha256`, which retains its live suite caller. Node syntax passed, the unchanged
PowerShell owner parsed with zero errors, and `git diff --check` passed apart from existing
line-ending warnings. The corrected Node file SHA-256 is
`1BEAE64C7C973EE976204104105E7A00E4686DF9CAF67917BB287D4FAAE197F4`; the unchanged PowerShell
file SHA-256 is `4DA35BA07C8C3A31D3F7C7D6DEEDB99F3AE28F7DC2682BE8203E52DAC2364955`. No Device/Web rerun,
build or upload followed this repository-only correction. P6-03 remains `in_progress`; closure,
staging, commit and publication remain withheld while cleanup ownership is under read-only review.

The independent cleanup-ownership review returned a terminal P6-03 closure `STOP` while accepting
the functional production evidence and assigning no firmware defect. The one-time dead-code
reviewer recheck returned `GO`, so that independent code blocker is cleared. Source and pinned-vendor
semantics confirm that `P2LARGECLEAN` executes synchronously through `SD.remove` into blocking
unlink/FatFs cluster-chain release and emits its serial result only after that operation completes.
The first cleanup command may therefore still have been running when its local observer failed, and
the later same-nonce command may have queued behind it. The corrected 120-second silence cannot
distinguish an already deleted file, an ongoing deletion or a retained file. This is a terminal
failure of the legacy P2-21 cleanup/device-storage transport path, not contrary P6-03 functional
evidence.

No further COM8 command or probe, HTTP/Web Console request, reset, build/upload or recovery action is
permitted on that failed path. The unchanged 347-byte ledger and both sanitized logs remain the
authoritative retained ownership evidence. P6-03 stays the sole `in_progress` row; staging, commit,
publication and P6-04 activation remain prohibited until genuinely new evidence is available from
an independently healthy interface. No user recovery or confirmation is required or requested.

Architect later superseded the earlier short-timeout path freeze solely to obtain one conclusive,
generously bounded cleanup observation under the user's standing Phase 6 authorization. After the
full visible plan was restored, the direct LF-delimited PowerShell holder revalidated nonce
`1789080570927`, the unchanged 347-byte ledger SHA-256
`AE6D5AF5283804EC08864182BF68E6E90453B43C5578AA8767FA7E02CD399550` and zero sidecars. It opened
COM8 once with DTR/RTS disabled, passively drained for two seconds, observed no buffered cleanup
result or readiness-loss marker, issued exactly one same-nonce `P2LARGECLEAN`, and waited under one
fixed 2,700,000-ms deadline. No exact, wrong-nonce, malformed or failing cleanup result, panic/reset
marker or serial I/O error arrived. At the 45-minute deadline it closed/disposed COM8, sent no final
idempotency command, deleted no ledger artifact and performed no reset, build/upload, HTTP or Web
Console action. The retained 297-byte sanitized log has SHA-256
`7DCB2A16531D9C28784AD354DA3EB18F3AF8D70E1FAF641E8C92AB26EEE08929`; the ledger remains
byte-for-byte unchanged with zero sidecars.

Architect finds this measured synchronous cleanup non-convergence qualifies for its recorded
reduction authority: further attempts create material Device and elapsed-time harm disproportionate
to one bounded, exact-owned, non-secret fixture on the user-declared disposable SD, while accepted
P6-03 production behavior and functional evidence are unaffected. `ROADMAP.md` therefore
quarantines this exact legacy P2-21 320 MiB fixture and validated ledger. Their deletion is excluded
only from P6-03 functional-row acceptance; the failed cleanup path must never be reused. The
quarantine remains mandatory P6-08 Phase 6 closure debt and may be removed only through a later
independently healthy interface or a documented disposable-SD baseline that preserves API
credentials and Wi-Fi configuration in NVS. This documentation correction does not complete P6-03,
authorize staging or publication, activate P6-04, or permit any Device, production, test or harness
change before Architect's personal minimality and closure review.

### P6-03 Architect closure GO

At `2026-09-11T17:48:38+03:00`, Architect personally reviewed the exact current canonical bytes,
the complete row-owned diff and retained evidence and returned explicit closure `GO`. The review
accepted the four persisted lifetimes, strict decode, cookie/CSRF side-effect ordering, RAM-only
until-reboot clearing, independent aggregate visible-tab heartbeat and Waiting transition,
multi-tab semantics, Busy/original-timestamp behavior, every mapped producer and consumer, the
applicable pinned-vendor timer and WebServer semantics, the generated Web asset, focused host/UI/
Device observations, resource floor and forbidden-effect checks.

The known legacy P2-21 320 MiB fixture and its validated ownership ledger remain explicitly
`UNKNOWN` and quarantined, not claimed cleaned. Their deletion is excluded only from P6-03
functional-row acceptance by the recorded Architect reduction, remains mandatory P6-08 closure
debt, and the failed cleanup path must not be reused. Publication requires no Device, build or
upload rerun.

The frozen publication set is exactly the 18 tracked row-owned paths. `ROADMAP.md` remains the
ignored local canonical scope file and is not staged. The Architect-approved unrelated untracked
`.codex/` and `m[1])` paths remain untouched. P6-04 is not activated before authenticated remote
SHA verification.

## P6-01 correction implementation and proof — 2026-09-16

**Correction interval:** 2026-09-15T22:39:54+03:00 through
2026-09-16T01:18:55+03:00. No unchanged-hypothesis stall reached a 30-minute
alert or 60-minute pivot threshold. New evidence successively assigned the observed
failures to palette inheritance, text-viewport ownership, upload cancellation
identity, two QA-oracle label mismatches, Device policy projection, degraded-SD
catalog state, danger-action contrast, persistent-settings footer content and
short-height Chat viewport ownership, fixed-menu close reachability and mobile
composer width.

The exact artifact-only inventory, design, proof matrix, non-goals and write set
were frozen before edits. The bounded independent pre-edit reviewer first returned
`STOP` because async upload failure/cancellation and unaffected Chat/Project
capability snapshots lacked direct proof. The corrected design added those
observations and the same reviewer performed its single blocker recheck, returning
`GO`: upload failure/cancellation is contained without mutation or console leakage,
BOM/native-byte identity is preserved, capability invalidation is correctly scoped,
and Web/Device unavailable states are directly observable. The adopted browser
semantics are W3C File API `Blob.arrayBuffer()` exact asynchronous byte reading and
WHATWG Encoding fatal UTF-8 decoding with BOM retained as content.

The only task-owned implementation file is
`C:/Users/84vs1/.codex/visualizations/2026/09/02/01a06386-22d5-7833-bb82-40a4f499f52e/p6-01-neutral-coverage-ia.html`.
The rejected input was 184,318 bytes at SHA-256
`D0B55029E1A1CFAE0CA596AC3AF3D1B52C470A2DFD070E7D6DB95E9469C2A16B`.
The final correction candidate is 201,354 bytes at SHA-256
20065781CC1C8618A79475DC17BEA21D3F61BA89A7919DB9BC4DF139DF6AF103,
a diagnostic increase of 17,036 bytes under the superseding no-byte-ceiling
decision. It remains one self-contained HTML/CSS/JS file with no dependency,
font, storage, timer, request or backend simulation.

The coherent correction keeps the existing information architecture while adding
the graphite/warm-gray/amber instrument palette and explicit readable foregrounds
for controls on dark headers, footers and composer surfaces; non-overlapping
natural-height collection rows; visible SD ready/unavailable state; distinct Web
source identities and exact URLs; API-shaped per-Chat capability snapshots with
Chat- and Project-scoped invalidation; the shipped editable-text extension set;
fatal UTF-8 rejection; exact text/BOM byte preservation; transfer-only bundle and
binary classification; and Device text paging from measured `clientHeight` and
`scrollHeight`. Device FileViewer consumes every existing content window, and
two-step host-key confirmation/result remains visible inside the 240x135 screen.
Device Project and Chat policy menus project the raw selected-record values, the
degraded-SD catalog explicitly shows unavailable state, and unselected danger
actions retain readable contrast. At 720x450 and 320x568, the Chat filter and
collection row remain operable while the selected-conversation transcript alone
owns overflow. The six existing per-message intent controls plus Output &
instructions and Available SSH tools reuse a native details menu whose compact
summary shows Auto, No tools or every selected required group. Its fixed centered
panel escapes existing clipping ancestors, and its local Done action only removes
the menu's open attribute. At the existing 640px breakpoint, Tools occupies the
first composer row and full-width Draft plus Send occupy the second; desktop and
720px retain the compact side-by-side composer.

The comprehensive disposable real-Chrome matrix passed on the immediate precursor
at SHA-256 A64760EE945EB6EF9E4E53AF540EA3B08BA048F08B04FF30916264FA1AE7CD40.
Its retained observations and 11 screenshots are in
C:/Users/84vs1/.codex/visualizations/2026/09/02/01a06386-22d5-7833-bb82-40a4f499f52e/p6-01-proof-a64760ee945e-2026-09-15T21-20-08-810Z/.
Observed coverage is 20 Web destination/viewport cases (four destinations at
1280x720, 900x720, 720x450, 390x780 and 320x568), all 10 Settings categories at
all five viewports (50 cases), and all 88 catalogued Device screens at 320x568.
Geometry checks found no page-level horizontal overflow, collection-row overlap,
clipped collection-row text, navigation-control overlap or selected Device row
outside its screen. The minimum measured contrast among the specifically corrected
enabled controls was 10.78:1. Architect retained this matrix for unchanged
boundaries and required only focused proof after each later concrete defect.

Seven upload observations passed: exact TXT and YAML content/native bytes;
BOM-bearing YAML retained U+FEFF and the original bytes; Project bundle and binary
remained transfer-only; malformed UTF-8 YAML was explicitly rejected with no
record; and a delayed old text read followed by close, reopen and a different file
left the new dialog open, committed neither identity and reported cancellation.
Only a later explicit Confirm can add the new selection. Both QA attempts that
used shortened capability labels stopped before acceptance; production remained
frozen, the oracle was corrected from the canonical displayed labels, and the full
matrix then passed.

Web and Device showed the exact initial capability snapshot. Saving one Chat made
only that Chat unavailable while another Chat retained all eight records. Saving
one Project made every Chat in that Project unavailable while the other Project
retained all eight records. Device Down/Up changed actual rendered text scroll
positions, exposed distinct first and final file-window text at 320x568, paged
FileEditor and capability status, traversed all seven SSH profile actions inside
the display, and showed the complete host-key prompt and result. Ready, missing,
removed, replaced and full SD states matched their required Device/Web presentation.
The second Web source showed the ESP32 title and `https://docs.espressif.com/`.
No page error, console error or external request occurred.

The focused policy/SD proof passed on the next correction candidate at SHA-256
9A2776C8CD1FBB28D2577E019E9E4082E63CF87CD79F686E982005679C9E163B.
Its retained evidence is in
C:/Users/84vs1/.codex/visualizations/2026/09/02/01a06386-22d5-7833-bb82-40a4f499f52e/p6-01-focused-9a2776c8cd1f-2026-09-15T21-30-15-650Z/.
All 10 Project-policy rows and all 10 Chat-policy rows exactly matched the selected
Web records; the degraded catalog showed SD unavailable and five normal SD
scenarios retained their required states. Three screenshots were retained, with no
page error, console error or external request.

The focused danger/settings proof passed on the following correction candidate at
SHA-256 5679ADA2821C1EA2DD59CB99F2C0D33FE70AC5D72199C7372256609AFC1B3E1F.
Its retained evidence is in
C:/Users/84vs1/.codex/visualizations/2026/09/02/01a06386-22d5-7833-bb82-40a4f499f52e/p6-01-style-5679ada2821c-2026-09-15T21-36-05-318Z/.
The Device danger text measured 10.26:1 contrast, and all five persistent mobile
Settings footers kept the complete Save action visible without the rejected
technical ownership note. Two screenshots were retained, with no page error,
console error or external request.

An intermediate focused short-layout proof executed candidate
EFBDFA467BB4E2B1BC447E95523DAD6B42E401E25A5D1B4A671BC92D925A234C.
Its retained evidence is in
C:/Users/84vs1/.codex/visualizations/2026/09/02/01a06386-22d5-7833-bb82-40a4f499f52e/p6-01-short-efbdfa467bb4-2026-09-15T21-41-40-333Z/.
At 720x450 the filter, readable selected row, Draft and Send controls were inside
their viewports and hittable. At 320x568 the detail view kept Draft and Send
inside and hittable, while the collection view kept the filter and readable rows
inside. All three cases had no horizontal overflow, page error, console error or
external request; three screenshots were retained. Architect then disproved its
closure claim: the transcript had only 23px client height at 720x450 and 21px at
320x568, so the visible conversation was a one-line slit. This candidate is
retained only as predecessor evidence for the unchanged collection geometry.

Candidate F406FF7E11DC2AC9841D880FD16A203C132BBC3BF725B7E9B7A1F1511EEE14AE
then moved the secondary composer controls into the existing native menu and
restored 121px/138px transcript client heights at 720x450/320x568. Architect
disproved that candidate too: at 320x568 its side-by-side Tools placement left the
Draft control only 65.30px wide, approximately 47px for text, so ordinary input
was unusable. That observation owns the final two-row mobile composer correction;
F406 is not closure evidence.

The final focused real-Chrome proof passed on SHA-256
20065781CC1C8618A79475DC17BEA21D3F61BA89A7919DB9BC4DF139DF6AF103.
Its observations and six screenshots are retained in
C:/Users/84vs1/.codex/visualizations/2026/09/02/01a06386-22d5-7833-bb82-40a4f499f52e/p6-01-chattools-20065781cc1c-2026-09-15T22-18-53-447Z/.
At 720x450 the transcript had 121px client height, 361px scroll height and a
real scrollTop of 21; the complete 65.98px two-line message, Tools, a 211px
content-width Draft and Send were simultaneously visible and hittable. At
320x568 the transcript had 98px client height, 479px scroll height and scrollTop
99; the complete 86.28px three-line message, the full-width Tools summary, a
213.30px Draft with 195px content width and Send were simultaneously visible and
hittable. At 1280x720 the complete transcript fit without requiring a scroll and
the 395px content-width Draft remained available.

At all three sizes the centered fixed menu stayed inside the viewport despite its
existing overflow-hidden ancestors. Auto, No tools, all four required groups, the
two existing option dialogs and Done were hit-testable; every menu control measured
10.78:1 contrast. On mobile, the closed summary exactly reflected No tools, Auto
and each accumulated required group. Open-to-Done, Output dialog Close-to-Done and
SSH tools cancel-to-Done preserved the exact selected Chat, draft and intent.
There was no page error, console error, external request or horizontal overflow.

Architect read the final source, personally inspected the final 320px Chat/menu
and 720px Chat screenshots, and reproduced the same three viewport boundaries in
direct Chrome on the exact final SHA. The independent observations and six
screenshots are retained in
C:/Users/84vs1/.codex/visualizations/2026/09/15/01a0a682-5410-7ed1-8f67-c2ab499bf055/prototype-audit/candidate-20065781/.
The raw local-HTTP response matched the exact 201,354 artifact bytes and final
SHA. System antivirus injected its own script into browser HTTP navigation, so the
CDP response-body hash differed; nothing in that environment was disabled, and
Architect's accepted browser proof used the exact native bytes through setContent.
Architect returned personal visual/functional GO and stated that every blocker in
the consolidated correction contract was closed; row-completion GO still awaits
the final canonical/cleanup reconciliation.

The phase agent personally inspected the retained desktop palette, 720x450 Shared
and SSH lists, 320x568 mobile palette, Settings and SFTP, 900x720 Device SFTP,
320x568 FileViewer first/final-window, final Device policy/degraded-SD, danger
contrast, persistent-footer, final Chat/message and open-menu screenshots at
720x450, 320x568 and desktop. Architect independently reproduced the principal
upload, source, viewport, SFTP, Device paging and host-key boundaries on earlier
candidates and personally accepted the final Chat boundary above. No row-completion
result is claimed until the separate explicit closure GO. All disposable QA
scripts, failed-run directories and temporary review PNG copies were removed; all
referenced successful evidence directories remain.

The suspended P6-04 production/test files were unchanged during this correction.
Their verified SHA-256 values are
198A86A9B2E2502EB51B047DE4F6A172DCA7E82167D5E7D93C0C4B4660BB86C2 for
the Web source,
2901D20D986F516BD6DA81733F66F23D9362D9782DC81DE7B7665BA7D3BF52E9 for
the server source,
6CF8DA42293BB3D3E3A2291DEC727C129439B594A89DE091EE550CC19FE9E797 for
the generated asset, and
B9F964FCE04D13FF147F5F359271D28A179DAEC210625CB510065BA461A2FE1D for
the retained Web test. No firmware, retained test, build, upload, HTTP or physical
Device action is P6-01 evidence. This prototype therefore does not claim production
runtime, resource or real-hardware acceptance. This evidence package remained
in progress until the explicit closure GO below; P6-04 stayed suspended and
untouched.

## P6-01 row-completion GO — 2026-09-16

At 2026-09-15T22:26:15Z (2026-09-16T01:26:15+03:00), Architect returned
explicit P6-01 ROW-COMPLETION GO after personally reconciling the final canonical
section, cleanup, changed source boundary, retained scoped observations and exact-SHA
browser/screenshots. Architect accepted the 201,354-byte artifact at SHA-256
20065781CC1C8618A79475DC17BEA21D3F61BA89A7919DB9BC4DF139DF6AF103 and
confirmed that all concrete blockers in the consolidated correction contract were
closed. The presentation-only residual is explicit; firmware runtime, resource and
release acceptance remain owned by P6-05, P6-06 and P6-08.

All phase-agent disposable QA scripts, failed proof directories and temporary PNG
copies are absent; every referenced successful evidence directory remains.
Architect also removed the exact-owned temporary comparison snapshot of the rejected
D0B55029 baseline after verifying its full hash, and verified its absence. The four
suspended P6-04 hashes above still match. P6-01 is completed. P6-04 remains pending
during the zero-active-row publication window and may become the sole active row
only after the exact P6-01 remote SHA is verified.
